

#ifdef __cplusplus
extern "C" {
	#endif
	
	#ifndef IMPLEMENTATION_H_
	#define IMPLEMENTATION_H_




	#define PA ((volatile uint8_t *) 0x21)						// Adresse des DDRA (Seite 96 Datenblatt)
	#define PB ((volatile uint8_t *) 0x24)
	#define PC ((volatile uint8_t *) 0x27)
	#define PD ((volatile uint8_t *) 0x2A)
	#define PE ((volatile uint8_t *) 0x2D)
	#define PF ((volatile uint8_t *) 0x30)
	#define PG ((volatile uint8_t *) 0x33)
	#define PH ((volatile uint8_t *) 0x101)
	#define PJ ((volatile uint8_t *) 0x104)
	#define PL ((volatile uint8_t *) 0x10A)
	#define PK ((volatile uint8_t *) 0x107)						// Adresse des DDRK (Seite 99 Datenblatt)



	typedef struct {
		volatile uint8_t * portreg;								// Addresse für das:	Port Register
		volatile uint8_t * datareg;												//		Data Register
		volatile uint8_t * pinreg;												//		Pin Register
	} digiport_t;


	// Legt Handler-Funktionen fest mit Typ DigiPort
	typedef digiport_t *digiport_h;
	digiport_t leds_ports;																//?????????
	digiport_t switch_ports;															//?????????
	digiport_h leds_h	= &leds_ports;
	digiport_h sw_h		= &switch_ports;


	// Legt Initialisierungs Funktion fest
	void initialize(digiport_t *digiport_arg, volatile uint8_t *temp, uint8_t mode) {
		(digiport_arg -> datareg) = temp;
		(digiport_arg -> portreg) = temp +1;
		(digiport_arg -> pinreg)  = temp -1;
		
		*(digiport_arg -> datareg) = mode;
	}

	// Funktion zum ausgeben eines Musters
	void write (digiport_t *digiport_arg, uint8_t mask)	{
		*(digiport_arg -> portreg) = ~(mask);								// ~ wegen aktive high
	}

	// Schaltet entsprechend einer Maske alle LED's aus
	void off (digiport_t *digiport_arg, uint8_t mask)	{
		*(digiport_arg -> portreg) 	|= (mask);
	}


	// Schaltet entsprechend einer Maske alle LED's ein
	void on (digiport_t *digiport_arg, uint8_t mask)	{
		*(digiport_arg -> portreg) &= ~(mask);
	}

	// Funktion zum invertieren der Bits
	void toggle (digiport_t * digiport_arg, uint8_t bits) {
		*(digiport_arg -> portreg) ^= (bits);
	}

	//Funktion lesen
	uint8_t read_raw (digiport_t * digiport_arg, uint8_t mask) {
		uint8_t ret_var;
		ret_var = ~((*(digiport_arg -> pinreg)) & mask);						// Schaut in Funktion mit Maske
		
		return ret_var;														//Rückgabewert
	}

	//Funktion Busy Waiting
	uint8_t read_busy_wait (digiport_t * digiport_arg, uint8_t mask) {
		uint8_t ret_val;
		
		do {
			ret_val = read_raw(digiport_arg, mask);
			
		}while(!ret_val);			//springt aus Schleife wenn gedrückt
		
		return ret_val;
	}
	
	

	#endif /* IMPLEMENTATION_H_ */

	#ifdef __cplusplus
	
}
#endif

