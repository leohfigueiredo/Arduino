int startPB = 7;
int initializePB = 8;
boolean initializeMachineBIT = true;  

//When the machine is turned on, 
//its initial state is initialized.  This means that each moveable part of the machine 
//is tied to its home position and will not come out of that state until the start button is pressed.
//This ensures that the machine is in a safe condition when turned on.
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(startPB, INPUT);
pinMode(initializePB, INPUT);
//We tie these inputs HIGH and pressing the button brings them LOW.
digitalWrite(startPB, HIGH);
digitalWrite(initializePB, HIGH);
//At machine startup, all containers are initialized and in their home positions.
digitalWrite(conveyor1InitializeBIT, HIGH);
digitalWrite(boxFillInitializeBIT, HIGH);
digitalWrite(conveyor2InitializeBIT, HIGH);
digitalWrite(tapeStationInitializeBIT, HIGH);
digitalWrite(conveyor3InitializeBIT, HIGH);
digitalWrite(eolPusherInitializeBIT, HIGH);
}
void loop() {
 digitalRead(initializePB);
 if (initializePB == LOW){
  initializeMachineBIT = true; 

  //If the "Initialize Machine" button is pressed, 
  //the initializeMachineBIT is true and all containers return to their initial states.

 }
 else{
initializeMachineBIT = false;//If the button is not pressed, the BIT is false.
}
  if (initializeMachineBIT == true){
 //At machine startup and whenever the "Initialize" Push button is pressed, 
 //all containers are initialized and return to their home positions.
digitalWrite(conveyor1InitializeBIT, HIGH);
digitalWrite(boxFillInitializeBIT, HIGH);
digitalWrite(conveyor2InitializeBIT, HIGH);
digitalWrite(tapeStationInitializeBIT, HIGH);
digitalWrite(conveyor3InitializeBIT, HIGH);
digitalWrite(eolPusherInitializeBIT, HIGH);  
 }

 int machineStart = digitalRead(startPB);


 //What comes next is the main event. This is the machine state sequencer. 
 //Look at it as a series of "if" statements. "If this is done, then start this. 
 //The sequencer will keep going forever until there is a fault or the user 
 //initializes the machine. 


 if (machineStart == 0){
   initializeMachineBIT = false;
 //The machine is taken out of Initialize when the START push button 
 //is pressed and the first state of the machine starts.
  conveyor1();
 }

  if (conveyor1CompleteBIT == true){ 
boxFill();
 }
if (boxFillCompleteBIT == true){
 conveyor2();
}
if (conveyor2CompleteBIT == true){
  tapeStation();
}
if (tapeStationCompleteBIT == true){
  conveyor3();
}
if (conveyor3CompleteBIT == true){
 eolPusher();
}
if (eolPusherCompleteBIT == true){
  conveyor1();

  //This line is very important as it loops the sequencer back to 
  //the beginning and will continue to loop until there is a fault 
  //or the user initializes the machine.

}
