# system-design-hw

## Start project
```bash
docker-compose up
```

# hw 1
- [x] MySQL db
    - [x] Table init (`Person` table)
        > Person should contain fields: login, first_name, last_name and age.
    - [x] Dockerize
    - [x] Add a constraint for `age` field ?
- [x] POCO REST service (C++)
    - [x] REST under `/person` endp.
        - [x] HTTP `GET` by login
        - [x] HTTP `GET` by first_name & last_name
        - [x] HTTP `POST` for root
            > POST parameters are: login, first_name, last_name and age.
    - [x] Link REST endpoints with db
    - [x] Integration testing
    - [x] Dockerize

## Test
Start the project.
```bash
docker-compose up
```
Wait until DB is up (didn't unclude `depends_on` in docker compose file, currently using version `3`), then start an integration testing with
```bash
python3 test.py
```

# hw 4
- [ ] SQL writer through a broker (RabbitMQ)
    - [x] Add RabbitMQ image with basic setup
    - [x] Separate writer thread from main server thread
    - [ ] Implement writer
