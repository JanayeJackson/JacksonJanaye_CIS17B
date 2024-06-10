INSERT INTO users 
(first_name, last_name, email, user_name, pass, registration_date) 
VALUES ('Larry', 'Ullman', 'email@example.com', 'testuser', SHA1('mypass'), NOW());

INSERT INTO admins
(first_name, last_name, email, user_name pass, add_date) 
VALUES ('Janaye', 'Jackson', 'jjackson169@student.rccd.edu','JJadmin' SHA1('mypassword'), NOW());

INSERT INTO catalog
(name, image, price, size) 
VALUES ('LEGO Ideas Home Alone', 'home.png', '299.99', '2'),
('Nintendo Entertainment System' 'nintendo.png', '269.99', '2'),
 ('R2-D2', 'r2d2.png', '239.99', '2'),
('LEGO Titanic', 'titanic.png', '679.99', '1'),
('Haunted House', 'haunted.png', '199.99', '2');

INSERT INTO enum_size (size_id, size) VALUES 
('1' , 'big' ),
('2' , 'medium'),
('3', 'small');