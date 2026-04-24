from datetime import datetime
from pydantic import BaseModel, Field
import json

class Register(BaseModel):
    offset: int
    name: str = Field(pattern="^[A-Za-z_][A-Za-z0-9_]*$")

class Peripheral(BaseModel):
    name: str = Field(...)
    base_address: int 
    size: int 
    enabled: bool
    registers: list[Register]
    
with open("spec_char.JSON") as conf:
    data = json.load(conf)          # Gives a dictionary of the file

periph = Peripheral(**data)

print(periph.model_dump())

