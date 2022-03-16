# system-design-hw

# hw 1
- [ ] MySQL db
    - [ ] Scheme init
    - [ ] Table init (`Person` table)
        > Person should contain fields: login, first_name, last_name and age.
    - [ ] Dockerize
- [ ] POCO REST service (C++)
    - [ ] REST under `/person` endp.
        - [ ] HTTP `GET` by login
        - [ ] HTTP `GET` by first_name & last_name
        - [ ] HTTP `POST` for root
            > POST parameters are: login, first_name, last_name and age.
    - [ ] Tests
        - [ ] Unit
        - [ ] Integration
    - [ ] Dockerize
