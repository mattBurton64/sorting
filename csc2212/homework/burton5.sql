#Matt Burton
#Homework 5
#67
select CHECK_NUM, BOOK_NUM, CHECK_OUT_DATE
from CHECKOUT
where CHECK_OUT_DATE < "2017-04-05"
order by CHECK_NUM;

#69
select BOOK_NUM, BOOK_SUBJECT, BOOK_TITLE, BOOK_COST
from BOOK
where BOOK_SUBJECT in ("Middleware", "Cloud") and BOOK_COST > 70
order by BOOK_NUM;

#70
select AU_ID, AU_FNAME, AU_LNAME, AU_BIRTHYEAR
from AUTHOR
where AU_BIRTHYEAR > 1979 and AU_BIRTHYEAR < 1990
order by AU_ID;

#80
select count(*) as "Available Books"
from BOOK
where PAT_ID is NULL

#85
select AU_ID, count(BOOK_NUM) as "Books Written"
from WRITES
group by AU_ID
order by count(BOOK_NUM) desc, AU_ID asc

#96
select AUTHOR.AU_ID, AU_FNAME, AU_LNAME, BOOK.BOOK_NUM, BOOK_TITLE
from AUTHOR
join WRITES on AUTHOR.AU_ID = WRITES.AU_ID
join BOOK on WRITES.BOOK_NUM = BOOK.BOOK_NUM
where BOOK_SUBJECT = "Cloud"
order by BOOK_TITLE, AU_LNAME;

#98
select BOOK.BOOK_NUM, BOOK_TITLE, count(CHECK_OUT_DATE) 'Times Checked Out'
from BOOK 
left join CHECKOUT on BOOK.BOOK_NUM= CHECKOUT.BOOK_NUM
group by BOOK.BOOK_NUM, BOOK_TITLE
order by count(*) desc, BOOK_TITLE;

#100
select AUTHOR.AU_ID, AU_LNAME, BOOK_TITLE, CHECK_OUT_DATE, PAT_LNAME
from AUTHOR 
join WRITES on AUTHOR.AU_ID = WRITES.AU_ID 
join BOOK on WRITES.BOOK_NUM = BOOK.BOOK_NUM 
join CHECKOUT on BOOK.BOOK_NUM = CHECKOUT.BOOK_NUM 
join PATRON on PATRON.PAT_ID = CHECKOUT.PAT_ID 
where AU_LNAME = "Bruer" and PATRON.PAT_LNAME = "Miles";

#101
select PATRON.PAT_ID, PAT_FNAME, PAT_LNAME 
from PATRON 
left join CHECKOUT on PATRON.PAT_ID = CHECKOUT.PAT_ID 
where CHECK_NUM is null

#105
select BOOK_NUM, BOOK_TITLE, BOOK_COST 
from BOOK 
where BOOK_COST = (select min(BOOK_COST) from BOOK) 
order by BOOK_NUM;

#106
select AU_ID, AU_FNAME, AU_LNAME
from AUTHOR
where AU_ID not in (select AU_ID from BOOK join WRITES on BOOK.BOOK_NUM
= WRITES.BOOK_NUM where BOOK_SUBJECT = 'Programming')
order by AU_LNAME

#108
select BOOK.BOOK_NUM, BOOK_TITLE, BOOK_SUBJECT, AU_LNAME, NUMBOOKS as
"Num Books by Author"
from BOOK 
join WRITES on BOOK.BOOK_NUM = WRITES.BOOK_NUM 
join (select AUTHOR.AU_ID, AU_LNAME, count(*) as NUMBOOKS
from AUTHOR join WRITES on AUTHOR.AU_ID = WRITES.AU_ID
group by AUTHOR.AU_ID, AU_LNAME) as AUTHBOOKS on
WRITES.AU_ID = AUTHBOOKS.AU_ID
where BOOK_SUBJECT = 'Cloud'
order by BOOK_TITLE, AU_LNAME;
