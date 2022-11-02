#Matt Burton
#Exam 2

#1
select city 
from customers 
where country in ('France') 
group by city 
having count(*) = 1

#2
select concat(contactLastName, ", " , contactFirstName) as 'Contact Name' 
from customers 
where city like "San%";

#3
select concat('$', format(sum(quantityOrdered * priceEach),2)) as 'Grand Total' 
from orderdetails;

#4
select distinct productVendor 
from products 
join orderdetails on products.productCode = orderdetails.productCode 
where buyPrice * 2.5 <= priceEach 
order by productVendor;

#5 FIX
select lastName as 'Last Name', firstName as 'First Name' 
from employees 
where reportsTo is not null 
and employeeNumber in 
	(select reportsTo from employees) 
order by lastName;

#6

#7 FIX
select firstName as 'First Name', lastName as 'Last Name' from employees where employeeNumber in (select reportsTo from employees group by reportsTo) and reportsTo is not null;

#8
select contactLastName, contactFirstName 
from customers c 
join orders o on c.customerNumber = o.customerNumber 
join orderdetails d on o.orderNumber = d.orderNumber 
join products p on d.productCode = p.productCode 
join productlines l on p.productLine = l.productLine 
where l.productLine in ('Ships') 
and d.priceEach * d.quantityOrdered >= 50000 
and o.orderDate - o.shippedDate <= 3 
order by c.contactLastName;
