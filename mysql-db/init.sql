use stud;

CREATE TABLE `person` (
  `login` varchar(255) NOT NULL,
  `first_name` varchar(255) NOT NULL,
  `last_name` varchar(255) NOT NULL,
  `age` int NOT NULL
);

INSERT INTO `person` (`login`, `first_name`, `last_name`, `age`) VALUES
('admin', 'Foo', 'Bar', 42),
('manager', 'Brew', 'Spencer', 22),
('adam', 'Adam', 'Smith', 16);

ALTER TABLE `person`
  ADD PRIMARY KEY (`login`);