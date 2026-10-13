// Output Pin Variables
const int pinRedOut = 9;
int redval = 0;
const int pinBlueOut = 8;
int blueval = 0;
const int pinYellowOut = 7;
int yellowval = 0;
const int pinGreenOut = 6;
int greenval = 0;

// Start Button
const int startButton = 0;
int butval = 0;
bool start = false;

//Analog Input Pins
const int detectRed = 4;
const int detectBlue = 3;
const int detectYellow = 1;
const int detectGreen = 2;

//Array
const int maxArraySize = 100;
int currentMax=0;
int currentDisplay=0;

//Game Variables
bool lose = false;
int totalPlayerInputs;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  randomSeed(analogRead(5));

  //Output Pins
  pinMode(pinRedOut, OUTPUT);
  pinMode(pinBlueOut, OUTPUT);
  pinMode(pinYellowOut, OUTPUT);
  pinMode(pinGreenOut, OUTPUT);
}

void loop() {
  //while loop that functions with a start button
  while(!start)
  {
    delay(100);
    //Serial.println("Button not pressed.");
    butval = analogRead(startButton);
    if(butval >= 400){
      start = true;
    }
  }
  Serial.println("Start button pressed");


  int randomArray[maxArraySize];
  // Initialize the array to be new random numbers;
  for(int i = 0; i < maxArraySize; i++)
  {
    randomArray[i] = random(6,10);
    // 6 - Green
    // 7 - Yellow
    // 8 - Blue 
    // 9 - Red
  }
  Serial.println("Finished initializing array");
  delay(100);
  currentMax = 2; // laways displays 3 lights to start


  // GAME BEGINS
  do // while the player has not lost
  {
    // Begin displaying all the random lights array starting from n=0 -> n=2
    for(int i = 0; i<= currentMax; i++)
    {
      digitalWrite(randomArray[i], HIGH);
      delay(900);
      digitalWrite(randomArray[i], LOW);
      delay(400);
    }
    
    //Shine all lights to signal the start of the players turn
    digitalWrite(pinRedOut, HIGH);
    digitalWrite(pinBlueOut, HIGH);
    digitalWrite(pinYellowOut, HIGH);
    digitalWrite(pinGreenOut, HIGH);
    delay(400);
    digitalWrite(pinRedOut, LOW);
    digitalWrite(pinBlueOut, LOW);
    digitalWrite(pinYellowOut, LOW);
    digitalWrite(pinGreenOut, LOW);    
    delay(300);

    //Accept player inputs
    while (totalPlayerInputs <= currentMax)
    {
      redval    = analogRead(detectRed);
      blueval   = analogRead(detectBlue);
      yellowval = analogRead(detectYellow);
      greenval  = analogRead(detectGreen);

      if (redval >= 400 || blueval >= 400 || yellowval >= 400 || greenval >= 400)
      {
        int pressed;
        if (redval >= 400)         pressed = pinRedOut;
        else if (blueval >= 400)   pressed = pinBlueOut;
        else if (yellowval >= 400) pressed = pinYellowOut;
        else                       pressed = pinGreenOut;

        delay(50);  // for button bounce

        // wait for release
        while (analogRead(detectRed) >= 400 || analogRead(detectBlue) >= 400 ||
              analogRead(detectYellow) >= 400 || analogRead(detectGreen) >= 400) {}

        delay(50);

        // check immediately
        if (pressed != randomArray[totalPlayerInputs]) {
         lose = true;
         break;
        }

      totalPlayerInputs++;
    }
  }
  totalPlayerInputs = 0;
  delay(100);

  if(!lose)
  {
    currentMax++;
  }

  }while(!lose);

  // GAME OVER: flash all lights, then reset
  for (int k = 0; k < 5; k++) {
   digitalWrite(pinRedOut, HIGH);
   digitalWrite(pinBlueOut, HIGH);
   digitalWrite(pinYellowOut, HIGH);
   digitalWrite(pinGreenOut, HIGH);
   delay(300);
   digitalWrite(pinRedOut, LOW);
   digitalWrite(pinBlueOut, LOW);
   digitalWrite(pinYellowOut, LOW);
   digitalWrite(pinGreenOut, LOW);
   delay(300);
  }


  lose = false;
  start = false;
  Serial.print("Game over. Rounds completed: ");
  Serial.println(currentMax - 2);
  Serial.println("Press start to start a new game :)");
}

