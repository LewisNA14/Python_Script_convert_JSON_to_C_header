from datetime import datetime
from pydantic import BaseModel, PositiveInt
import json

class Register(BaseModel):
    offset: int
    name: str

class Peripheral(BaseModel):
    name: str
    base_address: int
    size: int
    enabled: bool
    registers: list[Register]
    
with open("template.JSON") as conf:
    data = json.load(conf)          # Gives a dictionary of the file

periph = Peripheral(**data)

print(periph.name)

print(periph.model_dump())

