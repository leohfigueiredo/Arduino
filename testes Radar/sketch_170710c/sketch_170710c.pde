float circleX ;
float rectX;
float circleY ;
float rectY;

void setup() {

  size(600, 600);

  
}

void draw() {
background(255);
    //lógica
  
  circleX = random (width);
  rectY =  random(width);
  rectX =  random(height);
  circleY = random (height);  
  //Desenho
  fill(255, 100,50);
  ellipse(circleX, circleY, 24, 24);
   
  fill(100,0,200);
  rect(rectX, rectY, 24, 24);
  
sphere(100);
  

}