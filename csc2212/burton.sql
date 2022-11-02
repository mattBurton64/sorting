#Matt Burton Databse Final

#1
select firstName, count(firstName)
from student
group by firstName
having count(firstName) > 1
order by count(firstName) desc, firstName asc;

#2
select major, count(major) 
from student 
join enroll on student.studentid = enroll.studentID 
join class on enroll.classCode = class.classCode 
join course on class.courseCode = course.courseCode 
where course.courseCredit = 4 
and student.transfer = 'N' 
group by major 
order by count(major) desc;

#3
select student.firstName 
from student 
join enroll on student.studentid = enroll.studentID 
where enroll.enrollGrade = 'B' 
and enroll.enrollSemester = 1 
and enroll.enrollYear = 2018 
group by student.studentid 
having count(student.studentid) = 1 
order by student.firstName desc;

#4
select concat("GPA=",round(avg(student.GPA),2)) as "Average" 
from student 
join enroll on student.studentid = enroll.studentID 
join class on class.classCode = enroll.classCode 
where class.classTime like "Th%";

#5
select course.courseDescription, count(student.studentid) 
from enroll 
join student on enroll.studentID = student.studentID 
join class on enroll.classCode = class.classCode 
join course on class.courseCode = course.courseCode 
where enroll.enrollSemester = 2 
group by course.courseCode 
order by count(student.studentid) desc

#BONUS
begin

update enroll join class on class.classCode = enroll.classCode join course on class.courseCode = course.courseCode set enroll.enrollGrade = 'A' where course.courseDescription like "%database%"

commit;
