void getDistance(){

  if (previousLat != 0 && previousLon != 0) {
    distance = TinyGPSPlus::distanceBetween(currentLat,currentLon,previousLat,previousLon);
  }
  
  if(distance > 1.25){
    totalDistance += distance;
  }
}


void fareCalculator(){
  
  kmDistance = totalDistance/1000;
  if(kmDistance > 1.5){
    difference = kmDistance - variableReference;
    if(difference > 0.1){
      variableReference= variableReference + 0.1;
      if(int(variableReference*10) % 2 == 0){
        fareValue = fareValue + 2;
      }
      else{
        fareValue = fareValue + 1;
      }
    }
  }
}
