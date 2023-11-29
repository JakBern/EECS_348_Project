# ACTIVITY LOG FOR JAKE BERNARD
- Member Name: Jake Bernard
- Project Role: Project Manager
- Lab Section: 4 PM Thursday

# ENTRIES:
## 9/11/2023
### 11:48 AM - 11:49 AM
#### Activities
- Creating and sharing GitHub repo for project. Created first activity log.

## 9/17/2023
### 1 PM - 3PM, 4PM - 5:30 PM, 8 PM - 11:30 PM
#### Activities
- Filling out project plan.

## 9/20/2023
### 7:30 - 8:20
#### Activities
- Emailed Professor Saiedian some questions about the project
- Created member profile template, created member profile

### 11:00 - 11:50
#### Activities
  - Entered first meeting into meeting log
  - Created meeting checklist and meeting agendas
  - Entered agenda for next meeting
  - Created roles document, member profiles, reorganized repo

### 1:00 - 1:50
#### Activities
  - Updated to do log templates
  - Changed a little of project plan
  
## 9/17/2023
### 1:00 - 2:20
#### Activities
  - Migrated most documents to Markdown files
  - Continued filling out roles and responsibilities
  - Continued filling out project plan document, replacing example text sections

### 4:00 - 6:20
#### Activities
  - Started work on task overviews
  - Finished project plan
  - Contacted team about potential review order -- dropped in favor of single reviewer
  - Changed documents to fit Markdown syntax
  
## 9/24/2023
### 12:40 - 4:40 (on and off)
#### Activities
  - Redid Markdown files, adding tables of contents/updating organization
  - Updated role "Configuration Manager"
  - Updated Project Plan to reflect current organization patterns
  - Updated README
  - Created agenda for next meeting
  - Assigned weekly tasks to members

### 7:00 - 9:00
#### Activities
- Reread project plan and corrected typos/outdated information.
- Created Project Glossary
- Created Project Vision

## 9/25/2024
### 9:45 AM
#### Activities
- Added Software Requirements Specification

## 9/26/2024
### 10:30-10:50 AM
#### Activities
- Began filling out task overview

### 1:30 - 2:20 PM
#### Activities
- Continued filling out task overview


## 10/5/2023
### 10:30 - 11:45
#### Activities
- Created list of requirements
- Began filling out software requirements specification form
- looked into using Nuklear for GUI

## 10/8/2023
### 11:00 AM - 12:00 PM
#### Activities
- Continued filling out Software Requirements Specifications

### 10:15 PM - 11:00 PM
#### Activities
- Continued filling out Software Requirements Specifications
- Began reading through Nuklear documentation

## 10/9/2023
### 8:50 - 9:50 AM
#### Activities
- Aggregated teammates' suggestions for requirements document
- Continued filling out Software Requirements Specifications
- Continued reading through Nuklear documentation

## 10/14/2023 - 10/15/2023
### Various Times
#### Activities
- Finished Software Requirements Specifications with use case modeling

## 10/17/2023 - 10/18/2023
### Various Times
#### Activities
- Started actual programming
- Added main.cpp, helper.h, helper.cpp, flags.h, interface.h, cli.h, and cli.cpp
- Created the main loop

## 10/19/2023
### Various Times
#### Activities
- Continued working on base implementation
- Separated storage of runtime vars from AppInterface into UserContext
- looked into ncurses/conio.h for fancy TUI stuff (plan to use in a later iteration)

## 10/20/2023, 10/21/2023, 10/22/2023
### Various Times
#### Activities
- Finished hacky base implementation, pushed to project github
- NOTE: several questions were asked to Bing Chat on syntax/debugging questions, but all written code is original.

## 10/23/2023 - 10/24/2024
### Various Times
#### Activities
- Changed base implementation slightly, adding more features
- Reworked user context and parser to exist as distinct objects in main, parser and menu should hold shared pointers to user context
- interface will later hold a shared ptr to the parser

# 10/28/2023
## 11:50 - 5:30
### Activities
- Began work on making the "Value" class which holds numbers in symbolic form
- Also worked on the "BigNum" class which holds signed integers of arbitrary size
# 6:00 - 6:30
### Activities
- Worked on creating a UML class diagram for the project

# 10/29/2023
## 9:00 - 9:55 AM
### Activities
- Continued working on UML class diagram

# 11/2/2023
## 9:00 - 9:55 AM
### Activities
- Worked on grade-school multiplication for BigNum, researched Karatsuba algo

# 11/3/2023
## Various Times
### Activities
- Worked on implementation of divide-and-conquer division 
	- see: https://web.archive.org/web/20170708221722/https://static1.squarespace.com/static/5692a9ad7086d724272eb00a/t/5692dbe6b204d50df79e577f/1452465127528/masters-thesis.pdf
- Scrapped this and just added gradeschool division due to numbers not being stored as powers of 2

# 11/5/2023
## Various Times
### Activities
- Created 4 helpful diagrams to explain different mechanics of the software to team members
- Worked on Software Architecture document

# 11/11/2023
## 11 AM - 5 PM (intermittently)
### Activities
- Worked on Software architecture document

# 11/11/2023
## All day
### Activities
- Finished Software architecture document

# 11/21/2023
## 10:00 - 11:00 AM
### Activities
- Began commenting some previously uncommented code

## 12:30 - 1:30 PM
### Activities
- Continued commenting code
- changed/added some things to UserContext and TUI

# 11/28/2023
## Activities
- Met with team, discussed removing extraneous modules (mathnode, bignum, error codes, etc.) and focusing on core details of project
- Began debugging and rewriting parts of the UI
- Removed UI features that would not be necessary in the final implementation
- Changed several functions which returned flags (enums) to return strings instead