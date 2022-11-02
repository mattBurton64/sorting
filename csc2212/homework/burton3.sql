#19
select count(INV_NUMBER) as 'Total Invoices', sum(INV_TOT) as 'Total Sales', min(INV_TOT) as 'Minimum Sale', max(INV_TOT) as 'Largest Sale', avg(INV_TOT) as 'Average Sale' from (select    CUS_CODE, L.INV_NUMBER as INV_NUMBER, sum(L.LINE_UNITS * L.LINE_PRICE) as INV_TOT from INVOICE I, LINE L where I.INV_NUMBER = L.INV_NUMBER group by CUS_CODE, L.INV_NUMBER) IL; 

#20
select CUS_CODE, CUS_BALANCE from CUSTOMER where CUSTOMER.CUS_CODE in (select distinct CUS_CODE from INVOICE); 

#21
select min(CUS_BALANCE) as 'Minimum Balance', max(CUS_BALANCE) as 'Maximum Balance', avg(CUS_BALANCE) as 'Average Balance' from (select CUS_CODE, CUS_BALANCE from CUSTOMER where CUSTOMER.CUS_CODE in (select distinct CUS_CODE from INVOICE) 

#22
select sum(CUS_BALANCE) as 'Total Balance', min(CUS_BALANCE) as 'Minimum Balance', max(CUS_BALANCE) as 'Maximum Balance', avg(CUS_BALANCE) as 'Average Balance' from CUSTOMER; 

#23
select CUS_CODE, CUS_BALANCE from CUSTOMER where CUSTOMER.CUS_CODE not in (select distinct CUS_CODE from INVOICE);

#24
select sum(CUS_BALANCE) as 'Total Balance', min(CUS_BALANCE) as 'Minimum Balance', max(CUS_BALANCE) as 'Maximum Balance', avg(CUS_BALANCE) as 'Average Balance' from (select CUS_CODE, CUS_BALANCE from CUSTOMER where CUSTOMER.CUS_CODE not in (select distinct CUS_CODE from INVOICE)) as C;

#25
select P_DESCRIPT, P_QOH, P_PRICE, P_QOH * P_PRICE as Subtotal from PRODUCT;

#26
select sum(P_QOH * P_PRICE) as 'Total Value of Inventory' from PRODUCT;
