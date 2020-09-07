// Arreglo de botones y último estado del botón
// Nota: Los siguientes "DEFINE" son únicamente para
// mejorar la lectura del código al momento de codificar.
#define BTN_1  0
#define BTN_2  1
#define BTN_3  2
#define BTN_4  3

// Este arreglo contiene los pines utilizados para los botones
uint8_t button[4] = {
  2,
  3,
  4,
  5,
};

// Este arreglo contiene el último estado conocido de cada línea
uint8_t button_estate[4];

#define S_1   0 //S_HOME
#define S_2   1
#define S_3   2
#define S_4   3

uint8_t estado = S_1;

// Información de CHAVES
uint8_t r = 0;
uint8_t g = 0;
uint8_t b = 0;

#define rele00 8 // rele motor 3
#define rele02 9 // rele motor 3
#define rele08 10 // rele acionamento motor 3 e motor 4

void setup() {
  // Configurar como PULL-UP para ahorrar resistencias
  pinMode(button[BTN_1], INPUT_PULLUP);
  pinMode(button[BTN_2], INPUT_PULLUP);
  pinMode(button[BTN_3], INPUT_PULLUP);
  pinMode(button[BTN_4], INPUT_PULLUP);

  // Se asume que el estado inicial es HIGH
  button_estate[0] = HIGH;
  button_estate[1] = HIGH;
  button_estate[2] = HIGH;
  button_estate[3] = HIGH;

pinMode (rele00, OUTPUT); // define como saida
pinMode (rele02, OUTPUT); // define como saida
pinMode (rele08, OUTPUT); // define como saida
}
uint8_t flancoSubida(int btn) {
  uint8_t valor_nuevo = digitalRead(button[btn]);
  uint8_t result = button_estate[btn]!=valor_nuevo && valor_nuevo == 1;
  button_estate[btn] = valor_nuevo;
  return result;
}

// Máquina de estados
void loop() {
  switch(estado) {
    case S_1: /*** INICIO ESTADO S_HOME ***/
      if(flancoSubida(BTN_1)) { // Transición BTN_MENU
        estado = S_2;
        digitalWrite (rele00, HIGH); // envia saida para nivel alto
        break;
      }
      break; /*** FIN ESTADO S_HOME ***/
    case S_2: /*** INICIO ESTADO S_SET_R ***/
      if(flancoSubida(BTN_1)) { // Transición BTN_MENU
        estado = S_3;
digitalWrite (rele02, HIGH); // envia saida para nivel alto
        break;
      }
      if(flancoSubida(BTN_2)) { // Transición BTN_EXIT
        estado = S_1;
digitalWrite (rele08, HIGH); // envia saida para nivel alto
        break;
      }
      if(flancoSubida(BTN_3)) { // Transición BTN_UP
        if(r<255) {
          r++;
        } else {
          r = 0;
        }
        showColor();
        printRed();
        break;
      }
      if(flancoSubida(BTN_4)) { // Transición BTN_DWN
        if(r>0) {
          r--;
        } else {
          r = 255;
        }
        showColor();
        printRed();
        break;
      }
      break; /*** FIN ESTADO S_SET_R ***/
case S_3: /*** INICIA ESTADO S_SET_G ***/
      if(flancoSubida(BTN_1)) { // Transición BTN_MENU
        estado = S_4;
        printBlue();
        break;
      }
      if(flancoSubida(BTN_2)) { // Transición BTN_EXIT
        estado = S_1;
        printHome();
        break;
      }
      if(flancoSubida(BTN_3)) { // Transición BTN_UP
        if(g<255) {
          g++;
        } else {
          g = 0;
        }
        showColor();
        printGreen();
        break;
      }
      if(flancoSubida(BTN_4)) {
        if(g>0) {
          g--;
        } else {
          g = 255;
        }
        showColor();
        printGreen();
        break;
      }
      break; /*** FIN ESTADO S_SET_R ***/
case S_4: /*** INICIA ESTADO S_SET_B ***/
      if(flancoSubida(BTN_1)) { // Transición BTN_MENU
        estado = S_2;
        printRed();
        break;
      }
      if(flancoSubida(BTN_2)) { // Transición BTN_EXIT
        estado = S_1;
        printHome();
        break;
      }
      if(flancoSubida(BTN_3)) { // Transición BTN_UP
        if(b<255) {
          b++;
        } else {
          b = 0;
        }
        showColor();
        printBlue();
        break;
      }
      if(flancoSubida(BTN_4)) { // Transición BTN_DWN
        if(b>0) {
          b--;
        } else {
          b = 255;
        }
        showColor();
        printBlue();
        break;
      }
      break; /*** FIN ESTADO S_SET_R ***/
  };
}
