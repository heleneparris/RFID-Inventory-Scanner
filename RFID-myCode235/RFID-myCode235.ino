//THIS CODE WAS INSPIRED FROM USER: bragatheswaran17ei from the arduino project hub
//Link to source: https://create.arduino.cc/projecthub/bragatheswaran17ei/attendance-in-excel-sheet-using-rfid-rc522-593e56
//The PLX-DAQ program I am using was made by user: NetDevil on the arduino forum
//Link to source: https://forum.arduino.cc/t/plx-daq-version-2-now-with-64-bit-support-and-further-new-features/420628

//including relevant libraries
#include <SPI.h>          //allows arduino to communicate with Serial Peripheral Interface(SPI) programs, in this case it is communicating with the RFID scanner
#include <MFRC522.h>      //library that allows communication through built in functions with the RFID scanner

//giving constant values to the the RFID pins
#define SS_PIN 10
#define RST_PIN 9

MFRC522 RFID(SS_PIN, RST_PIN);    //creating RFID scanner object
String card_ID = "";              //creating a String that will be used later to compile and store the RFID tag ID

//Adding String vars that represent the RFID tag ID #
//this will be used later to assign the Name and Student ID variables to each RFID tag #
String student1 = "19422116527";
String student2 = "227159220154";
String student3 = "23716874186";
String student4 = "15019671177";
String student5 = "939473186";
String student6 = "3423519";

//this will be used later to assign the gearName and inventory# variables to each RFID tag #
String gear1 = "6623525527";
String gear2 = "82245519";
String gear3 = "109161114186";
String gear4 = "22124170186";
String gear5 = "173251200186";
String gear6 = "1781661228";

int ledPin = 8;           //vars for led pin
int buzPin = 7;           //vars for piezo buzzer pin
boolean readyToPrint;     //boolean that will be true if the variables shouls be printed in the serial monitor
int numCards[6];          //array that holds how many RFID tag objects there are in the code
int n = 0;                //vars that helps the program recognize if a card has been read before
int Status[6];            //array that will determine the 'status' (if they have checked the gear back in or not) of the ID. Used for time IN and time OUT
int s = 0;                //vars that stores the 'staus' of each IDint x;
int checkOutArray[100];   //array that will store the Gear_ID of each scan
int rentalNumArray[100];  //array that will store the rental # of each scan
int x;                    //vars for the checkOutArray[] index
int y;                    //vars for the rentalNumArray[] index

String Name;              //vars that assigns the student's name
long Student_ID;          //vars that assigns the students ID #
int Rental = 0;           //vars that idicates which rental this is
String gearName;          //vars that assigns the gear name
long Gear_ID;             //vars that assigns the gear inventory #

//---------------------------------------------------------------------------

void setup() {
  Serial.begin(9600);         //begin communication via serial port
  SPI.begin();                //begin communication to RFID scanner
  RFID.PCD_Init();            //library function that initializes the MFRC522 chip
  readyToPrint = false;       //initially making this boolean false
  pinMode(ledPin, OUTPUT);    //initializing the led pin
  pinMode(buzPin, OUTPUT);    //initializing the buzzer pin
  x = 0;                      //setting the initial indices as 0
  y = 0;
}

void loop() {
  //if statements that check if there is a card being read by the RFID scanner:
  //the 'PICC_IsNewCardPresent()' command returns true if there is a card being read
  if ( ! RFID.PICC_IsNewCardPresent()) {
    return;     //if there is no card then do not return anything
  }

  //the 'PICC_ReadCardSerial()' command returns true if a card could be read
  if ( ! RFID.PICC_ReadCardSerial()) {
    return;     //if there is not a card being read, then return nothing
  }

  //figuring out what the RFID id # is
  //for loop reads the entire ID # coming in and puts the ID values into an array
  //the ID values are then assigned to the card_ID vars
  card_ID = "";                      //resetting the card_ID string to be blank after each scan
  for (byte i = 0; i < RFID.uid.size; i++) {
    Serial.println(RFID.uid.uidByte[i]);
    card_ID += RFID.uid.uidByte[i];
  }

  //if statements that will assign values to each RFID tag # as it is read
  //if the ID # is equal to one of the previously mentioned ID #'s, then the student ID number and name are assigned
  //also changes 'n' and 's'
  if (card_ID == student1) {
    Name = "Helen Parris";
    Student_ID = 515395;
    n = 0;
    s = 0;
    readyToPrint = false;     //this is false so that values are not sent to the serial monitor until a gear tag is scanned
  }
  else if (card_ID == student2) {
    Name = "Rosa Wheelen";
    Student_ID = 516232;
    n = 1;
    s = 1;
    readyToPrint = false;
  }
  else if (card_ID == student3) {
    Name = "John Doe";
    Student_ID = 500384;
    n = 2;
    s = 2;
    readyToPrint = false;
  }
  else if (card_ID == student4) {
    Name = "Chris Whitmire";
    Student_ID = 555920;
    n = 3;
    s = 3;
    readyToPrint = false;
  }
  else if (card_ID == student5) {
    Name = "Zane Cochran";
    Student_ID = 513029;
    n = 4;
    s = 4;
    readyToPrint = false;
  }
  else if (card_ID == student6) {
    Name = "Sarah Appleseed";
    Student_ID = 500384;
    n = 5;
    s = 5;
    readyToPrint = false;
  }
  //similar if statements, but for the gear tags
  if (card_ID == gear1) {
    gearName = "Backpack";
    Gear_ID = 23;
    n = 0;
    s = 0;
    readyToPrint = true;
  }
  else if (card_ID == gear2) {
    gearName = "Paddleboard";
    Gear_ID = 13;
    n = 1;
    s = 1;
    readyToPrint = true;
  }
  else if (card_ID == gear3) {
    gearName = "Tandem Kayak";
    Gear_ID = 22;
    n = 2;
    s = 2;
    readyToPrint = true;
  }
  else if (card_ID == gear4) {
    gearName = "Sleeping Bag";
    Gear_ID = 16;
    n = 3;
    s = 3;
    readyToPrint = true;
  }
  else if (card_ID == gear5) {
    gearName = "4-Person tent";
    Gear_ID = 11;
    n = 4;
    s = 4;
    readyToPrint = true;
  }
  else if (card_ID == gear6) {
    gearName = "Cooking Kit";
    Gear_ID = 14;
    n = 5;
    s = 5;
    readyToPrint = true;
  }

  //if statement that will trigger the led and buzzer
  if (card_ID == student1 || student2 || student3 || student4 || student5 || student6 || gear1 || gear2 || gear3 || gear4 || gear5 || gear6) {
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
    digitalWrite(buzPin, LOW);
  }

  //if statements that will print out corresponding values when a card is read
  //checking if the slot in the numCards array reads 1 (meaning that it is the second card that is stored)
  //checking the status to see if the card has been read already (0 means it hasn't been read yet)
  if (numCards[n] == 1 && Status[s] == 0 && readyToPrint == true) {
    Status[s] = 1;                        //changes the status to "1" so the next time the card is read, the time will be logged in the "Time OUT" column in Xcel
    numCards[n] = 0;                      //switches n to zero so the next time it's read, it will print out again, but with the Return time

    //for loop that loops thru the array and will match returns with their original checkout Rental #
    int tempRental = Rental;
    for (int i = 0; i < 100; i++) {               //loop thru the array
      int tempI = checkOutArray[i];               //store the value of the index in this temp vars
      if (Gear_ID == tempI) {                     //check to see if the Gear_ID of the scanned card is in the array
        tempRental = rentalNumArray[i] + 1;       //if it is, then the rental # is equal to the subsequent index of the RNA[] (the original rental #)
      }
    }
    //then print all the relevant values to the serial monitor
    Serial.print("DATA,");
    Serial.print(tempRental);
    Serial.print(",");
    Serial.print("DATE");
    Serial.print(",");
    Serial.print(Name);
    Serial.print(",");
    Serial.print(Student_ID);
    Serial.print(",");
    Serial.print(gearName);
    Serial.print(",");
    Serial.print(Gear_ID);
    Serial.print(",");
    Serial.print("");
    Serial.print(",");
    Serial.println("TIME");
  }

  else if (numCards[n] == 0 && readyToPrint == true) {  //if the gear tag has already been scanned
    numCards[n] = 1;
    Status[s] = 0;

    checkOutArray[x] = Gear_ID;    //storing each Gear_ID and Rental vars in the array
    rentalNumArray[y] = Rental;
    x ++;                          //increasing the index for the next event
    y ++;
    Rental ++;

    //then print all the data to excel
    Serial.print("DATA,");
    Serial.print(Rental);
    Serial.print(",");
    Serial.print("DATE");
    Serial.print(",");
    Serial.print(Name);
    Serial.print(",");
    Serial.print(Student_ID);
    Serial.print(",");
    Serial.print(gearName);
    Serial.print(",");
    Serial.print(Gear_ID);
    Serial.print(",");
    Serial.print("TIME");
    Serial.print(",");
    Serial.println("");
  }
  delay(1000);   //delay so the card wont be read multiple times when it's held over the RFID scanner
}
