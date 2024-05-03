# Minimal Viable Product {#dmm_mvp}

## General

- Modbus Serial

## Modbus Master

- Modbus Init, Start, Stop and Deinit
- Tracking taken Slave-Addresses
- Adjustable Baud-Rate

## Slave Device

- Read/Write Holding Registers

## Error Handling

- Timeouts may be a special case -> User can specify Number of Retries per Device + Log
- OK need not be handled
- Invalid Response, Not Supported and Fail -> Log + return to User to handle