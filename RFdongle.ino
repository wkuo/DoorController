void debugDongle(){
  Serial.print("YK04: A - " + String(module->isA()));
  Serial.print(" | B - " + String(module->isB()));
  Serial.print(" | C - " + String(module->isC()));
  Serial.println(" | D - " + String(module->isD()));
}

