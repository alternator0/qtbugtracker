# QTbugtracker
Bug tracking software written in c++ with qt framework

# Get Started
- You need to have installed PostgreSQL server, cmake and Qt Creator
- Create a database with
```
  "host=localhost "
  "dbname=bugtracker "
  "user=postgres "
  "password=changeme"
```
- Create table with
```
  CREATE TABLE bugs (
    id SERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    priority INT NOT NULL,
    comment VARCHAR(1000),
    time TIMESTAMP(0)  NOT NULL DEFAULT CURRENT_TIMESTAMP
);
```
- Lastly build it in Qt Creator

# Screenshots
![image](https://github.com/alternator0/SpaceInvaders/assets/135737229/af1e4c6a-2e88-4981-b656-fd29e296c592)
