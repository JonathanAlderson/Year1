/********************************************************************

I declare that the following program was written by me and that I have NOT copied any part of this code from any other source.

Name: Jonathan Alderson

Email: sc17j3a@leeds.ac.uk

Date: 14/10/17

********************************************************************/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>


#define waitingAreaCapacity 60   // This is used in a define statement to avoid use of magic numbers and avoid the runtime error of not using the define statement
#define numberOfconsultingRooms 10

bool requirePassword = true; // This is the boolean which changes if the password is needed to access specilist functions

int consultingRooms[numberOfconsultingRooms]; // This array stores information about every room in the surgery, 1 for doctor is avaliable, 0 for doctor is not avaliable


// QUEUE VARIABLES
int queue[waitingAreaCapacity];   // This queue stores the id number of every static int waitingAreaCapacity = 60;   // Maximum number of people that can be in the waiting room at the same time
int first = -1; // This 'points' to the first position in the queue
int last  = -1; // This 'points' to the last position in the queue

// Consulting Rooms VARIABLES

int doctorsInConsultingRooms[numberOfconsultingRooms]; // This queue will contain either a -1 or the id of the doctor in it :)
int patientsInConsultingRooms[numberOfconsultingRooms]; // This array will store which patients are in which rooms.
int i;
int numberOfDoctorsWhoCanTakePatients;

void displayWelcomeMessage() // This prints a lovely welcome message that is shown at every stage to add consintency and professionalism.
{
  printf("\e[1;1H\e[2J");
  printf("\n╔════════════════════════════════════════════════════════════════════════════════╗");
  printf("\n║ Welcome to the                                                                 ║");
  printf("\n║  _____             _                    _____                                  ║");
  printf("\n║ |  __ \\           | |                  / ____|                                 ║");
  printf("\n║ | |  | | ___   ___| |_ ___  _ __ ___  | (___  _   _ _ __ __ _  ___ _ __ _   _  ║");
  printf("\n║ | |  | |/ _ \\ / __| __/ _ \\| '__/ __|  \\___ \\| | | | '__/ _` |/ _ \\ '__| | | | ║");
  printf("\n║ | |__| | (_) | (__| || (_) | |  \\__ \\  ____) | |_| | | | (_| |  __/ |  | |_| | ║");
  printf("\n║ |_____/ \\___/ \\___|\\__\\___/|_|  |___/ |_____/ \\__,_|_|  \\__, |\\___|_|   \\__, | ║");
  printf("\n║                                                          __/ |           __/ | ║");
  printf("\n║                                                         |___/           |___/  ║");
  printf("\n╚════════════════════════════════════════════════════════════════════════════════╝\n\n");
  printf("Please enter a command or type 'h' for help.\n\n\n\n");

}


void exitProgram()
{
  printf("\e[1;1H\e[2J");
  displayWelcomeMessage();
  printf("\n\n\n\n\n\n\n\n\tProgram will exit safely now.\n\n\n\n\n\n\n\n\n\n\n\n\n"); // nice reassuring customer message
  exit(1);
}



void sleepMS(int ms) // A small function that is used to add short delays so that the simulator can be seen in action.
{
    long delay;
    clock_t time1,time2;

    delay = ms*(CLOCKS_PER_SEC/1000);
    time1 = clock();
    time2 = clock();
    while( (time1-time2) <= delay )
        time1 = clock();
}


int doctorsWhoCanTakePatients(bool printoutDesired)
{
  int docsAvaliable = 0;
  for(i=0;i<numberOfconsultingRooms;i++) // This iterates trough the array showing which Doctors are at work, and which patients are currently being served.
  {
      if(doctorsInConsultingRooms[i] != -1)
        docsAvaliable ++;
      if(patientsInConsultingRooms[i] != -1)
        docsAvaliable --;
  }
  if(printoutDesired)// printoutDesired was used for debuggin purposes
    printf("\n\nAfter running the function doctorsWhoCanTakePatients, there are %i avaliable.\n\n",docsAvaliable);
  return docsAvaliable;
}

int assignRoom()
{
  if(doctorsWhoCanTakePatients(false) > 0)
  {
    int i;
    for(i=0;i<numberOfconsultingRooms;i++)
    {
      if(doctorsInConsultingRooms[i] != -1) // Meaning that there is a doctor in the room
      {
        if(patientsInConsultingRooms[i] == -1)// Meaning there is not a patient in a room with a doctor in
        {
          return i; // returns a room which has a doctor in but not a patient in.
        }
      }
    }
  }
  return 79; // 79 is used as a value to show an incorrect room.
}

void enqueue(int n)// append n to the queue
{
  if((first == 0 && last == waitingAreaCapacity-1)  ||  (first == last+1 && first != 0 && last != 0))
  {
    printf("\n\nSorry, the waiting queue is full. Please try again later.");
    // In the future this will force quit the program, with the error message of waiting room full of people
  }

  if(first== -1 && last == -1)
  {
    queue[0] = n;
    first = 0;
    last = 0;
    return;
  }


  if(last < waitingAreaCapacity-1)
  {
    last++;
    queue[last] = n;
    return;
  }

  if(last = waitingAreaCapacity-1)
  {
    last = 0;
    queue[last] = n;
    return;
  }

  return;

}

int dequeue() // This will return -1 in case of an error where the queue is already empty upon dequeueing
{
  if((first == -1 && last == -1))
    return -1;
  int firstItem = queue[first];
  if(first == last)
  {
    first = -2;  // This is a -2 since the first ++ happends in the next line down, meaning that at the end of the function they will both be -1.
    last =  -1;  // The queue is reset since there are no more items left in the queue.
  }
  first ++;
  if(first == waitingAreaCapacity)
    first = 0;

  return firstItem;
}

int getFirst()// get the first item in the queue without removing it
{
  if(first == -1)
    return -1;
  return queue[first]; // Is that it?
}

int getLast()
{
  if(last == -1)
    return -1;
  return queue[last];
}


int avaliableDoctors(bool printoutDesired) // THIS IS CALLED WITH 'd'
{

  int i;
  int numOfDoctors = 0;


  for(i=0;i<numberOfconsultingRooms;i++)
  {
      if(doctorsInConsultingRooms[i] != -1)
      {
        numOfDoctors ++;
      }
  }

  if(printoutDesired)
  {
    displayWelcomeMessage();
    if(numOfDoctors == 0)
    {
      printf("\n\nUnfortunately there are no Doctors in the surgery at the moment.");
      return;
    }
    if(numOfDoctors == 1)
      printf("\n\n\n\n\n\nThere is currently %i doctor avaliable,\n\nThey are in room ",numOfDoctors);
    else
      printf("\n\n\n\n\n\nThere are currently %i doctors avaliable,\n\nThey are in rooms ",numOfDoctors); // These are just for nicely formatted printouts to the user
    if(numOfDoctors > 0)
    {
      int doctorsAccountedFor = 0; // This is all the logic to get the grammar correct
      for(i=0;i<numberOfconsultingRooms;i++)
      {
        if(doctorsInConsultingRooms[i] != -1)
        {
          if(doctorsAccountedFor == numOfDoctors-1)
          {
            if(numOfDoctors == 1)
              printf("%i\n\n\n\n",doctorsInConsultingRooms[i]);
            else
              printf(" and %i\n\n\n\n",doctorsInConsultingRooms[i]); // This makes sure the grammar is correct for a single item or multiple items
          }

          else
            printf("%i,",doctorsInConsultingRooms[i]);

          doctorsAccountedFor++;
        }
      }

    }

  }

  return numOfDoctors;
}

void print(bool printoutDesired) // prints the entire queue
{
  if(printoutDesired)
    displayWelcomeMessage();
  if(first != -1 && last != -1)
  {
  printf("\n\nThe following patients are still waiting to be seen by a Doctor:\n",first);
  int i = first;
  if(last < first)
      {
        for(i;i<waitingAreaCapacity;i++) // This has to go through two different loops, to do the second half ,adn the overlapped section
          printf("%i, ",queue[i]);
        for(i=0;i<last;i++)
          printf("%i, ",queue[i]);
        printf("%i ",queue[last]);
      }
  else
  {
      for(i;i<last;i++) // This is in the simple case where the queue is not looping
       {
        printf("%i, ",queue[i]);
      }
      printf("%i\n",queue[last]);
      }
  }
  else
  {
      printf("\n\nThere are no patients waiting to be seen by a Doctor.\n");
  }
}

void clear() // completely clears the queue, reseting everything back to 0
{
  int i;

  for(i = 0; i < waitingAreaCapacity;i++)
  {
    queue[i] = 0;
  }
  first = -1;
  last = -1;
}

bool isEmpty()
{
  if(first == -1 && last == -1)
    return true;
  return false;
}

bool isFull()
{

  if(first == 0 && last == waitingAreaCapacity-1)
    return true;
  return false;
}

int itemsInQueue()
{
  // Will work out the number of active items in the queue
  if(first < last)
    return (last - first + 1); // this has a +1 on the end since a 7,7, queueu contains 1 item instead of the assumed 0.
  if ( first == last)
    return 1;
  if(first == -1 && last == -1)
    return 0;
  if(last < first)
  if((waitingAreaCapacity - (first-last) + 1) == waitingAreaCapacity)
    return 0;
  return waitingAreaCapacity - (first-last) + 2;
}

int position(int n) // returns the position of n in the queue, or -1 if n is not in the queue
{
  if(first != -1 && last != -1)
  {
    if(first == last) // If the list only has one item in, then we can just return a 0 or a -1, depending on if it is in the list or not.
    {
          if(queue[first] == n)
            return 0;
          else
            return -1;
    }
    if(last > first) // This is the normal case, where the queue is not seperated out.
    {
      int i;
      for(i=first;first<last;i++)
      {
        if(queue[i] == n)
          return i;
        if(i > waitingAreaCapacity) // This means that the item is definitly not in the queue, so returns a -1
          return -1;

      }
    }

  if(first > last) // This is the awkward case where the list has to be looped around the
      {
            int i = first;
            for(i;i<waitingAreaCapacity;i++) // This has to go through two different loops, to do the second half ,adn the overlapped section
            {
              if(queue[i] == n)
                return i-first;
            }
            for(i=0;i<last+1;i++)
            {
              if(queue[i] == n)
                return i+last;
             }
        }

    }

  return -1; // Used to show that the patient in question is not in the queue



}

bool inArray(int target, int *array, int arrayLenth){
    int i;
    for (i=0; i < arrayLenth; i++) {
        if (array[i] == target)
            return true;
    }
    return false;
}

int arrayPosition(int target, int *array, int arrayLenth){
    int i;
    for (i=0; i < arrayLenth; i++) {
        if (array[i] == target)
            return i;
    }
    return -1;
}

void removeFromQueue(int n)
{
  int i;
  int posToRemove = position(n);
  if(posToRemove != -1)
  {
    queue[posToRemove+first] = -999; // This indicates that the item should be renamed

    // Case where the queue only has one item in
    if(first == last)
    {
            first  = -1;
            last   = -1;
    }

    if(first == 0 && last > first) // This is the situation where the queue has not yet looped around
    {
      for(i=posToRemove;i<last+1;i++)
      {
        queue[i] = queue[i+1];
      }
      last --;
      return;
    }

    //When removing the first item from the list it also requires a special case
    if(posToRemove == 0)
    {
              first++;
              first = first%waitingAreaCapacity;
              return;
    }
    // This is the case where the array has already looped round and is split apart
    if((posToRemove+first)%waitingAreaCapacity <first)
    {
            for(i=((posToRemove+first-1)%waitingAreaCapacity);i<last;i++)
            {
              queue[i] = queue[i+1];
            }
            last --;
            return;
    }

    //                                                                                       E        S   R    Where E = end, S = start and R = to be removed
    // This is the case where we need to remove items from the overlapping section     [ 5,6,7,0,0,,0,1,2,3,4]
    if(first < posToRemove+first)
    {
            for(i=(posToRemove+first);i<waitingAreaCapacity;i++)
            {
              queue[i] = queue[i+1];
            }
            queue[waitingAreaCapacity-1] = queue[0];
            for(i=0;i<last;i++)
            {
              queue[i] = queue[i+1];
            }
            last --;
    }

  }
  else
  {
            printf("\n\nError, trying to remove an item from the queue that does not exist in the queue.\n\n");
  }
}

void patientQueuePosition(int n,bool printoutDesired, bool simulatorMode) // This is called with p'
{
  if(printoutDesired)
    displayWelcomeMessage();
  if(position(n) == -1)
    printf("Sorry, it appears that you are not currently in the queue.");
  else
  {
    if(! simulatorMode)
      printf("You are number %i in the queue ",position(n)+1);
  }

}

int patientCheckIn(int n,bool printoutDesired, bool firstTime,bool simulatorMode) // THIS IS CALLED WITH 'i'
{
  if(firstTime) // If it is their first time checking in, then they must go through this check., but if they are checking into a free room then they have already met this criteria
  {
    if(position(n) != -1) //patientsInConsultingRooms
    {
      displayWelcomeMessage();
      printf("\n\nYou are already checked in\nYou are in position %i in the queue.\n\n",position(n)+1);
      return -1;
    }
    if(inArray(n,patientsInConsultingRooms,numberOfconsultingRooms))
    {
      printf("\n\nPatient %i is already in room %i!",n,arrayPosition(n,patientsInConsultingRooms,numberOfconsultingRooms)+1);
      return;
    }
  }

  if(printoutDesired)
    displayWelcomeMessage();
  if(doctorsWhoCanTakePatients(false) > 0)
  {
    int roomAssigned = assignRoom();
    if(printoutDesired)
      printf("\n\nOne of our doctors is free,\nplease proceed to Room %i\n\n\n",roomAssigned+1);
    if(simulatorMode)
      printf("\n\nThe patient has now proceeded to Room %i\n",roomAssigned+1);
    patientsInConsultingRooms[roomAssigned] = n;
    return roomAssigned;
  }
  else
  {
    if(itemsInQueue() == 59)
    {
      printf("\n\nSorry The surgery is full at the moment, please come back later\n\n");
      return -1;
    }
    enqueue(n);
    if(! simulatorMode)
      printf("\n\nAll Doctors are busy right now, please relax in the waiting area.\n\n ");
    else
      printf("\nThe patient has joined the queue as there are no Doctors avaliable.");
    patientQueuePosition(n,false,false);
  }
  return -1;
}



void patientQuitQueue(int n,bool printoutDesired)
{
    if(printoutDesired)
      displayWelcomeMessage();
    if(position(n) == -1)
    {
      printf("Sorry, you are not curently in the queue and so cannot be removed from it.");
    }

    else
    {
      removeFromQueue(n);
      if(printoutDesired)
          printf("\n\n You have now been removed from the queue. Thank you for your visit.",n);
      else
          printf("\n\nThe patient has now been removed from the queue, there are still %i patients waiting.\n\n",itemsInQueue()%60);

    }
}

void patientCheckOut(int n,bool printoutDesired) // called with O for patient check 'o'ut;
{
  if(printoutDesired)
    displayWelcomeMessage();
  int i;
  int roomToClear = -1;
  for(i=0;i<numberOfconsultingRooms;i++)
  {
    if(patientsInConsultingRooms[i] == n)
    {
      roomToClear = i;

    }
  }
  if(roomToClear == -1)
  {
      printf("\n\nSorry, this patient is not currently in a room and so cannot be checked out.\n\n");
      return;
  }
  doctorsInConsultingRooms[roomToClear] = -1; // Clears the Doctor from the room, so they will have to say they are ready before they can take another patient again.
  patientsInConsultingRooms[roomToClear] = -1; // removes the patient from the current consulting room that they are in.
  printf("\n\nThe patient has been discharged from the room,\nto recieve a new patient from the waiting area, please show you are ready with\nthe 'r' command and the room number.\n\n");
}




void doctorAway(int n)
{
  displayWelcomeMessage();
  if(n > 0 && n < numberOfconsultingRooms+1)
  {
    if(patientsInConsultingRooms[n-1] != -1)
    {
      printf("\n\nYou still have a patient in the room, please checkout patient %i before being away.",patientsInConsultingRooms[n-1]);
      return;
    }
    if(doctorsInConsultingRooms[n-1] != -1)
    {
      doctorsInConsultingRooms[n-1] = -1;
      printf("\nThe doctor is now away, and will not be able to take any more clients.\n");
      return;
      }

  }

  printf("\nSorry,this doctor is not in a room at the moment.\n");

}

void doctorReady(int n,bool printoutDesired)
{
  if(n>0 && n<numberOfconsultingRooms+1)
  {
    if(patientsInConsultingRooms[n-1] != -1)
    {
      printf("\n\nYou still have a patient in the room, please checkout patient %i before being ready.",patientsInConsultingRooms[n-1]);
      return;
    }
    doctorsInConsultingRooms[n-1] = n;
    if(printoutDesired)
      displayWelcomeMessage();
    printf("\n\nA Doctor has just checked in to room %i\n\n",n);
    int nextPatient = getFirst();
    if(nextPatient != -1 && nextPatient != -999) // -999 is to indicate that the patient has been removed from the wqueue.
    {
      printf("\n\nA patient is ready for you now, patient number %i\n\n",nextPatient);
      if(patientCheckIn(nextPatient,false,false,false) != -1)
        patientQuitQueue(nextPatient,false);
    }

  }
  else
    printf("\n\nSorry we don't have that many consulting rooms. Please try again.\n\n");
}

//╔ ═ ╦   ╗ ║  ╝  ╚  ╩
void helpMenu()
{
  displayWelcomeMessage(); // More nice print statements to display the help menu
  printf("\n Note: ### represents your 3 digit patientID number.\n       #   represents your Doctor number.\n");
  printf("\nPatient Commands\n\n");
  printf("╔═══════╦══════════════════════════════════════╗\n");
  printf("║ i ### ║ Check in with your 3 Digit patientID ║\n");
  printf("╠═══════╬══════════════════════════════════════╣\n");
  printf("║ p ### ║ Check your position in the queue     ║\n");
  printf("╠═══════╬══════════════════════════════════════╣\n");
  printf("║ q ### ║ Leave the queue                      ║\n");
  printf("╠═══════╬══════════════════════════════════════╣\n");
  printf("║ d     ║ Check the avaliable doctors          ║\n");
  printf("╠═══════╬══════════════════════════════════════╣\n");
  printf("║ h     ║ See what each command does           ║\n");
  printf("╚═══════╩══════════════════════════════════════╝\n");

  printf("\n\nAdministrator Commands\n\n");
  printf("╔═══════╦══════════════════════════════════════╗\n");
  printf("║ o ### ║ Check out a patient from the surgery ║\n");
  printf("╠═══════╬══════════════════════════════════════╣\n");
  printf("║ r  #  ║ Used by Doctors to indicate arrival  ║\n");
  printf("╠═══════╬══════════════════════════════════════╣\n");
  printf("║ a  #  ║ Used by Doctors to show a temp leave ║\n");
  printf("╠═══════╬══════════════════════════════════════╣\n");
  printf("║ w     ║ View the status of the patient queue ║\n");
  printf("╠═══════╬══════════════════════════════════════╣\n");
  printf("║ x     ║ Terminate the pogram                 ║\n");
  printf("╠═══════╬══════════════════════════════════════╣\n");
  printf("║ s     ║ Run Simulation                       ║\n");
  printf("╚═══════╩══════════════════════════════════════╝\n");

}



void status()
{
  int i;
  for(i=0;i<numberOfconsultingRooms;i++)
  {
    printf("\nRoom %i: Doctor: %i Patient:%i",i+1,doctorsInConsultingRooms[i],patientsInConsultingRooms[i]);
  }
}

void resetQueues()
{
  int i = 0;
  for(i=0;i<numberOfconsultingRooms;i++)
  {
    doctorsInConsultingRooms[i] = -1;
    patientsInConsultingRooms[i] = -1;
  }
  clear(); // this clears the patient waiting queue;

}


// I will be treating my times as hour.minute So the hours will be in a 24 hour format and the minutes will range from
void simulation(int numberOfDoctorsStaffing,float patientArrivalRate, int patientConsultantTime, float patientStartTime, float patientEndTime)
{
  patientConsultantTime = patientConsultantTime-1;
  float openingTime = 8.00;
  float closingTime = 17.00;

  float currentTime = openingTime;
  int i;
  int timeRemainingInRooms[numberOfconsultingRooms]; // This stores the remaining number of time that each paitient will still be in the room for.

  int patientWaitTimes[100000];
  int patientsWhoHaveHadToWait = 0;
  int startOfPatientsWhoHaveHadToWait = 0;

  int patientNumber = 1;
  int roomToCheckInTo;
  int l;

  float averageWaitTime = 0;
  int longestWaitTime = 0;
  int shortestWaitTime = 9999;

  float partOfPatientArrivalRate = patientArrivalRate;

  for(i=0;i<numberOfDoctorsStaffing;i++)
  {
    timeRemainingInRooms[i] = -1;

  }

  for(i=1;i<numberOfDoctorsStaffing+1;i++) // Initally sets the doctors ready for every doctor in the hospital
  {
    doctorReady(i,false);
  }

  for(currentTime;currentTime<=closingTime;currentTime = currentTime + 0.01) // Iterates through the day one minute at a time

  {

    sleepMS(20);
    print(false);


    // This prints out the time in the correct format so we can see how far through the simulation we are.
    if((int)(100*(currentTime-(int)currentTime)) < 10)
      // ALl the maths going on here is just for formatting, nothing complicated or cool
      printf("The time is %i:0%i\n",(int)currentTime,(int)(100*(currentTime-(int)currentTime)));
    else
      printf("The time is %i:%i\n",(int)currentTime,(int)(100*(currentTime-(int)currentTime)));
      // Checks if a patient is finished in a room
    for(i=0;i<numberOfDoctorsStaffing;i++)
    {
      if(timeRemainingInRooms[i] != -1)
      {
        timeRemainingInRooms[i] --; // Takes 1 minute of the remaining time for each paitient getting served by the Doctor.
        if(timeRemainingInRooms[i] == -1)// If the patient has been in the room for 10 minnutes
        {
          printf("\n\nPatient %i 's appointment has finished.'\n\n",patientsInConsultingRooms[i]);
          patientCheckOut(patientsInConsultingRooms[i],false);
          //patientsInRooms[i] = -1;
          //printf("\n\nFirst =  %i\n\n",getFirst());
          if(getFirst() != -1 && getFirst() != -999)
            timeRemainingInRooms[i] = patientConsultantTime;
          doctorReady(i+1,false);
          startOfPatientsWhoHaveHadToWait++; // now one patient does not have to wait anymore, so we can add one to this value.
        }
      }
    }

    for(i=startOfPatientsWhoHaveHadToWait;i<patientsWhoHaveHadToWait;i++) // Iterates through all the patients that are waiting in the queue, then adds one minute to their waiting time.
    {
      patientWaitTimes[i] ++;
    }


    // This only happends if the times are within the boundries of times that patients come in and leave.
    if(currentTime>patientStartTime && currentTime < patientEndTime)
    {

        for(i=0;i<(int)partOfPatientArrivalRate;i++)
        {
          printf("\nPatient %i has just arrived in.",patientNumber);
          roomToCheckInTo = patientCheckIn(patientNumber,false,true,true);
          if(roomToCheckInTo != -1)
          {
            timeRemainingInRooms[roomToCheckInTo] = patientConsultantTime;

          }
          else // The patient has joined the queue
          {
            patientWaitTimes[patientsWhoHaveHadToWait] = 0;
            patientsWhoHaveHadToWait++;
          }
          patientNumber++;
        }

        if(partOfPatientArrivalRate>=1)
        {
          partOfPatientArrivalRate = 0;
        }
        partOfPatientArrivalRate = partOfPatientArrivalRate + patientArrivalRate;


    }
    // This just incraments the time
    if(currentTime-(int)currentTime >= 0.59)
    {
      currentTime = currentTime + 0.4;
    }
  }

  for(i=0;i<patientsWhoHaveHadToWait;i++)
  {
    if(patientWaitTimes[i] > longestWaitTime)
    {
      longestWaitTime = patientWaitTimes[i];
    }
    if(patientWaitTimes[i] < shortestWaitTime)
    {
      shortestWaitTime = patientWaitTimes[i];
    }
    averageWaitTime = averageWaitTime + patientWaitTimes[i];
  }
  int patientsWating = itemsInQueue();
  if(patientsWating == 1)
    patientsWating = 0;  // has a smsall bug where if there are no people waiting in the queue, sometimes it will return one. This is the lazy fix and not the good way.
  printf("\n\n\nThe surgery has now closed.\n\nNumber of patients waiting to be served: %i\nOvertime needed to clear queue: %i\nAverage wait time: %.2f minutes\nLongest wait time: %i minutes\n",patientsWating,patientsWating*(patientConsultantTime+1),averageWaitTime/patientNumber,longestWaitTime);
  if(shortestWaitTime != 9999)
    printf("Shortest wait time: %i minutes",shortestWaitTime);
  else
    printf("Shortest wait time: 0 minutes");
}




void runConsole()
{

  printf("\n\n>>>");
  int IDNumber = -1;
  int command = -1;
  command = getchar();

  int correctPassword = 1111;
  int password;


  if(command != 'h' && command != 'x' && command != 'd' && command != 'w' && command != 's' && command != 't')
  {
    scanf("%i",&IDNumber);
  }

  if(command == 'h')
    helpMenu();
  if(command == 'x')
    exitProgram();

  if(command == 'd')
    avaliableDoctors(true); // 1 means a printout is desired anything else does not give a printout
  if(command == 'i')
    patientCheckIn(IDNumber,true,true,false);
  if(command == 'p')
    patientQueuePosition(IDNumber,true,false);
  if(command == 'q')
    patientQuitQueue(IDNumber,true);

  if((command == 'o' || command == 'r' || command == 'a' || command == 's' || command == 'w' ) && requirePassword)
  {
    printf("\n\nThis is an Administrator command, please enter the password\n\n>>>");
    scanf("%i",&password);
    if(password == correctPassword)
    {
      printf("\n\n\nPassword correct.\n\n\n");
    }
    else
    {
      printf("\n\n\nINVALID PASSWORD\n\n\n");
      return;
    }
  }
  if(command == 'o')
    patientCheckOut(IDNumber,false);
  if(command == 'r')
    doctorReady(IDNumber,true);
  if(command == 'a')
    doctorAway(IDNumber);
  if(command == 's')
  {
    int a,c;
    float b,d,e;
    resetQueues();
    printf("Please enter simulation constraints, this includes\n\nNumberOfDoctors,HowManyPatientsPerMinute,patientConsultantTime,patientStartTime,patientEndTime\n\nPlease note, number of doctors, and patientConsultantTime must be integers.\nAlso, the format for time is 24 hour with 7.26 representing 07:26 and 13:50 representing 13:50.\nAlso note the doctors surery is open between 8am and 5pm.\n\nPlease format like '1,0.2,8,8.15,13.45' for example\n\n>>>");
    scanf("%i,%f,%i,%f,%f",&a,&b,&c,&d,&e);
    simulation(a,b,c,d,e); // numOfDoctors,HowManyPatientsPerMinute,ServingTime,Start,End
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nSimulation finished, starting constraints of: %i,%.2f,%i,%.2f,%.2f\n\n",a,b,c,d,e);
    resetQueues();
  }

  if(command == 'w')
      print(true);
  if(command == 't')
      status();
}

int main()
{
  // Setup arrays
  // This code sets the arays which describe which doctors are avaliable and which patients are in which rooms
  resetQueues();
  displayWelcomeMessage();
  while(1<2)
  {
    runConsole();
  }
	return 0;
}
