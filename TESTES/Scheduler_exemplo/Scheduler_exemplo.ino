/** 
 *  TaskScheduler Test
 *
 *  Initially only tasks 1 and 2 are enabled
 *  Task1 runs every 2 seconds 1 time and then stops
 *  Task2 runs every 3 seconds indefinitely
 *  Task1 enables Task3 at its first run
 *  Task3 run every 5 seconds
 *  Task1 disables Task3 on its last iteration and changed Task2 to run every 1/2 seconds
 *  At the end Task2 is the only task running every 1/2 seconds
 */
 
 
#include <TaskScheduler.h>
int porta_rele1 = 7;

int estadorele1 = 1;

int leitura1 = 0;


// Callback methods prototypes
void t1Callback();
void t2Callback();
void t3Callback();

//Tasks
Task t4();
Task t1(2000, 1, &t1Callback);
Task t2(3000, 1, &t2Callback);
Task t3(5000, 1, &t3Callback);

Scheduler runner;


void t1Callback() {
   
   //Verifica o acionamento do botao 1
  leitura1 = digitalRead(porta_botao1);
  if (leitura1 != 0)
  {
    while(digitalRead(porta_botao1) != 0)
    {
      delay(1000);
    }
    //Inverte o estado da porta
    estadorele1 = !estadorele1;
    //Comandos para o rele 1
    digitalWrite(porta_rele1, estadorele1);
    
    if (t1.isLastIteration()) {
      runner.addTask(t2);
      t2.enable();
      Serial.println("t1: enabled t3 and added to the chain");
    }
    
    if (t2.isLastIteration()) {
      t2.disable();
      runner.deleteTask(t2);
      t2.setInterval(500);
      Serial.println("t1: disable t3 and delete it from the chain. t2 interval set to 500");
    }
}

void t2Callback() {
    Serial.print("t2: ");
    Serial.println(millis());
  
}

void t3Callback() {
    Serial.print("t3: ");
    Serial.println(millis());
  
}

void setup () {

  pinMode(porta_rele1, OUTPUT); 
  pinMode(porta_botao1, INPUT);



digitalWrite(porta_rele1, HIGH);

  Serial.begin(115200);
  Serial.println("Scheduler TEST");
  
  runner.init();
  Serial.println("Initialized scheduler");
  
  runner.addTask(t1);
  Serial.println("added t1");
  
  runner.addTask(t2);
  Serial.println("added t2");

  delay(5000);
  
  t1.enable();
  Serial.println("Enabled t1");
  t2.enable();
  Serial.println("Enabled t2");
}


void loop () {
  runner.execute();
}
