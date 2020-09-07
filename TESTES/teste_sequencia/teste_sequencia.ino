int   led1 = 13;
int   led2 = 14;
int   led3 = 15;
int   count = 0;

void loop  () 
{
if (count % 3 == 0) 
digitalToggle(led1);
if (count% 7 == 0)
digitalToggle(led2);
if (count%11 == 0)
digitalToggle(led3);
if (count == 3 * 7 * 11)
count = 0;
count++;
delay(1000);
}
