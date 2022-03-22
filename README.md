# system-design-hw

# hw 1
- [x] MySQL db
    - [x] Table init (`Person` table)
        > Person should contain fields: login, first_name, last_name and age.
    - [x] Dockerize
    - [ ] Add a constraint for `age` field ?
- [ ] POCO REST service (C++)
    - [x] REST under `/person` endp.
        - [x] HTTP `GET` by login
        - [x] HTTP `GET` by first_name & last_name
        - [x] HTTP `POST` for root
            > POST parameters are: login, first_name, last_name and age.
    - [x] Link REST endpoints with db
    - [ ] Unit tests
    - [x] Dockerize
