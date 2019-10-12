/* printing blank space */

.print ''
.print ''
.print ''

/* Question 10 */
.print 'All Modules sorted by the number of students taking them'
.print ''
CREATE TABLE Teaches(Lecturer text , Module int);
CREATE TABLE Studies(Student text, Module int, Grade int );
.separator ','
.import PartBData/TeachesData Teaches
.import PartBData/StudiesData Studies

SELECT Module, COUNT(*) FROM Studies GROUP BY Module ORDER BY COUNT(*) DESC;
.print ''
.print 'Task ten complete'


.print ''
.print 'Listing each lecturer with the number of unique people they lecture'
.print ''

.mode column
.headers on

/*SELECT  Teaches.Lecturer, Studies.Student FROM Teaches INNER JOIN Studies ON Teaches.Module = Studies.Module;*/
.print ''


SELECT  Lecturer,COUNT(Lecturer) FROM (SELECT DISTINCT Teaches.Lecturer, Studies.Student FROM Studies INNER JOIN Teaches ON Studies.Module = Teaches.Module) GROUP BY Lecturer;

.print ''
.print 'Task 11 Complete'

.print ''
.print 'Showing each lecturer, the modules they teach, and the number of students that do each module'
.print ''

/* SELECT Lecturer,Module,Student FROM (SELECT DISTINCT Teaches.Lecturer,Teaches.Module, Studies.Student FROM Studies INNER JOIN Teaches ON Studies.Module = Teaches.Module); */



SELECT  Lecturer,Module,COUNT(Student) FROM (SELECT Lecturer,Module,Student FROM (SELECT DISTINCT Teaches.Lecturer,Teaches.Module, Studies.Student FROM Studies INNER JOIN Teaches ON Studies.Module = Teaches.Module)) GROUP BY Lecturer,Module ORDER BY Lecturer;
.print ''
.print 'Task 12 Complete'


.print ''
.print 'Number of modules in which everyone passed'
.print ''

SELECT COUNT(*) FROM (SELECT DISTINCT Module from Teaches EXCEPT SELECT  Module FROM (SELECT DISTINCT Teaches.Module, Studies.Grade FROM Studies INNER JOIN Teaches ON Studies.Module = Teaches.Module WHERE Grade < 40));

.print ''
.print 'Task 12 Complete'
