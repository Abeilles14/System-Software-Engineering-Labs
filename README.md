# System-Software-Engineering-Labs
System Software Engineering (CPEN)  
- Isabelle Andre
- Justin Chang

A third year Computer Engineering course consisting of 6 labs and 2 assignments using C++ and UML.  
Topics Include Operating systems principles, real-time systems, principles of concurrent and multi-threaded programming,
information structures, introduction to object oriented analysis, design, and modelling using UML, testing of software systems.

### Lab 1: Object Oriented Programming
* Creating Classes, Objects, Member Functions, Accessors, and Mutators.
* Simulating Turning On and Off multiple light bulbs, lamps, and switches using OOP and ADS concepts such as
pointers, Linked Lists, Inheritance, Templates, etc.

### Lab 2: Concurrency Part 1
* Creating an application composed of several separate programs/processes all running together at the same time
* Writing a multi-tasking system using multiple child processes controlled by a parent process
* Creating Processes and Child processes running in active and suspended state
* Passing parameters or information to the 3 child processes and print out the data the parent process has passed to
the child processes
* Write a multi-threaded solution, i.e. write a single parent process comprising several child threads
built into the same source file using the CThread class
* Removing *rt.cpp* and *rt.h* and replacing the CThread and CProcess classes by variables and code that
call the windows kernel directly using the C++ 11 threading library which is built into Visual Studio

### Lab 3: Concurrency Part 2
* Creating Active classes CoffeeMaker and WashingMachine
* Designing  a simple software state machine for each class that captures its behaviour as a series of States
* eg. A washing machine initially starts in the IDLE state. When it receives a message, it should transition
through the FILLING, WASHING, DRAINING, SPINNING states
* Printing CoffeeMaker and WashingMachine statuses
* Creating multiple instances of WashingMachine and CoffeeMaker to run concurrently
* Creating two more Child threads in each Active classes such as WaterInletValve and a Motor, then running
and controlling these concurrent child threads

### Lab 4: Inter-Process Communication
* Establishing communication between processes and threads in a distributed/concurrent application
* Using a Datapool to send data to 2 Child programs from a Parent program
* Reading Data from Pipelines and Typed Pipelines concurrently from child processes
* Using Sockets as a means of inter-process communication for distributed system. The Parent/Client can
send a command to the Child/Server along with parameters that represent some action to be performed.
The Child carries out the action and returns back to the parrent an appropriate response via sockets

### Lab 5: Thread and Process Synchronisation Communication
* Mutual Exclusion and using a Mutex to correct the problem
* Creating an Active class and 3 child threads inside active class outputting to screen
* Fixing Mutual Exclusion using a C++ 11 style Atomic Flag then a Mutex
* Writing a "Named" Monitor class to protect access to terminal output window by embedding a hidden Mutex
into the Monitor class
* Modifying the project to become a Single Producer, Double Consumer Problem
* Modifying the project to become a Double Producer, Single Consumer using two data pools: one for each
producer and a polling algorithm in the consumer

### Lab 6: Complex Synchronization
* Writing a program to simulate a ‘pit-stop’ in a motor race
* A ‘pit stop’ involves a driver bringing their car into the ‘pit’ to carry out routine maintenance on
the car such as a change of tires and refuelling
* 18 technicians are involved in each pit stop
* During a race, a driver can decide to make a pit stop if for example, they are low on fuel or their
tires need changing. All drivers share the same pit lane and technicians
* Each time they complete a lap of the circuit, a driver can check a red/green pit entry light
positioned at the entrance of the pit lane
* Technicians have to coordinate with their other team members to ensure that a certain sequence of
events is observed
* The driver and the technicians are all represented by active objects. The simulation is designed using
Semaphores as the only means of synchronization
* The simulation of the motor race involves at least 10 cars and 20 laps, and displays the status of each
race cars, drivers, and pitstop technician

### Assignment 1: Designing a Ten-Story Duplex Elevator System Simulation
https://github.com/Abeilles14/Elevator-System-Simulation
* An elevator system simulation model of a ten-story duplex using concurrent programming, multi-threading,
and thread synchronization.
* A double elevator system responds to requests made either from within the elevator, or from requests made outside the elevator for transportation of passengers up or down and to the specified destination floors.
* Both Elevator status are displayed at all time using monitors, including elevator direction, general status, door status, and current floor number

### Assignment 2: Designing a University System and Database
https://github.com/Abeilles14/University-System-Database
* A mock cmd line University System and non-persistent database for engineering professors and student
courses, grades, enrollment, applications, etc.
* Computerizes traditional paper-records or spreadsheet approach of running a University such as UBC
* User-Case, Sequence, and Class Diagrams are created using UML before mapping into code
* Every Actor (Student, Professor, Admin, President) inherit user properties, and possess a userID,
username, and password to Login.







