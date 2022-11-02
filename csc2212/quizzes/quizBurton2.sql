#Matt Burton
#Quiz second chance
#1

select BOOK_SUBJECT, count(*) as "Books in Subject"
from BOOK 
group by BOOK_SUBJECT 
order by count(*) desc
limit 3;

#2
select concat(PAT_FNAME, " ", PAT_LNAME) as "Full Name" 
from PATRON 
join CHECKOUT on PATRON.PAT_ID = CHECKOUT.PAT_ID 
where CHECK_IN_DATE > CHECK_DUE_DATE 
order by PAT_LNAME;

#3
select upper(AU_LNAME) as "Author's Last Name", BOOK_TITLE as "Book Title", concat("$",BOOK_COST) as "Book Cost" 
from AUTHOR 
join WRITES on AUTHOR.AU_ID = WRITES.AU_ID 
join BOOK on WRITES.BOOK_NUM = BOOK.BOOK_NUM 
where BOOK_COST >= 60 and BOOK_COST <= 80 
order by BOOK_COST desc, AU_LNAME;
