/* printing blank space */
/* seting printout methods */
.mode column
.headers on
.print ''
.print ''
.print ''

/* Question 1 */
.print ''
CREATE TABLE shopping( Product text PRIMARY KEY,Quantity int);

INSERT INTO shopping(Product,Quantity)
VALUES('Jam',1);
INSERT INTO shopping(Product,Quantity)
VALUES('Bread',2);
INSERT INTO shopping(Product,Quantity)
VALUES('Tea',5);
INSERT INTO shopping(Product,Quantity)
VALUES('Cereal',1);

SELECT * FROM shopping;
.print ''
.print 'Task one complete'


/* Question 2 */
.print ''
CREATE TABLE products( Product text PRIMARY KEY, Price INT);
.separator ','
.import ProductData products

SELECT * FROM products;
.print ''
.print 'Task two complete'


/* Question 3 */
.print ''
.print 'The number of items in both tables are'
SELECT COUNT(*) FROM (SELECT Product from shopping INTERSECT 	SELECT Product from products);

.print 'Task three complete'


/* Question 4 */
.print ''
.print 'The number of items bought on the shopping trip were'
SELECT SUM(Quantity) FROM (select Quantity from shopping WHERE 	Product IN (SELECT Product FROM shopping INTERSECT SELECT 	Product FROM products));

.print 'Task four complete'


/* Question 5 */
.print ''
.print 'Products in the shop with a price over 120'
SELECT Product FROM products WHERE Price > 120;

.print 'Task five complete'


/* Question 6 */
.print ''
.print 'Shopping receipt'
SELECT shopping.product, Quantity * Price FROM products INNER JOIN shopping ON products.Product = shopping.Product;

.print 'Task six complete'


/* Question 7 */

.print ''
.print 'Total cost is'
SELECT SUM(Quantity * Price) FROM products INNER JOIN shopping ON products.Product = shopping.Product;

.print 'Task seven complete'


/* Question 8 */
.print ''
SELECT Quantity * Price FROM products INNER JOIN shopping ON products.Product = shopping.Product WHERE shopping.Product = 'Tea';
.print 'Question nine complete'

/* Question 9 */
.print ''
.print 'Tea and Jam cost this much'
SELECT SUM(Quantity * Price) FROM products INNER JOIN shopping ON products.Product = shopping.Product WHERE shopping.Product = 'Tea' OR shopping.Product = 'Jam';
.print 'Question ten complete'
