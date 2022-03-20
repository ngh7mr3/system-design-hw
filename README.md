# system-design-hw

# hw 1
- [x] MySQL db
    - [x] Table init (`Person` table)
        > Person should contain fields: login, first_name, last_name and age.
    - [x] Dockerize
    - [ ] Add a constraint for `age` field ?
- [ ] POCO REST service (C++)
    - [ ] REST under `/person` endp.
        - [ ] HTTP `GET` by login
        - [ ] HTTP `GET` by first_name & last_name
        - [ ] HTTP `POST` for root
            > POST parameters are: login, first_name, last_name and age.
    - [ ] Unit tests
    - [x] Dockerize
