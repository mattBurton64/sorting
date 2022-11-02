#Matt Burton
#1
select count(*) as 'Total items sold on sale'
from PRODUCT
where P_DISCOUNT > 0;

#2
select P_DESCRIPT
from PRODUCT
where P_PRICE > 2 * (select avg(P_PRICE) from PRODUCT)
order by P_QOH desc;

#3
select distinct CUS_FNAME, CUS_LNAME
from CUSTOMER join VENDOR on CUS_CODE 
where V_STATE in ('GA', 'TN') and V_ORDER in ('Y');
order by CUS_LNAME;

