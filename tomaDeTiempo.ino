//declaración de los pines
int pin_tendedora = 7;
int pin_cortadora = 6;
int pin_recogido = 8;
//formato cronometro
byte seconds;
byte minutes;
byte hours;
//verificadores
int cont_tendedora = 0;
int cont_cortadora = 0;
int cont_recogido = 0;
boolean ver_tendedora = false;
boolean ver_cortadora = false;
boolean ver_recogido = false;
//almacenamiento
String alm_tendedora = "Tiempo total de la tendedora: ";
String alm_cortadora = "Tiempo total de la cortadora: ";
String alm_recogido = "Tiempo total del recogido: ";
String alm_total = "Tiempo total del proceso: ";
int arraytimeTotal[3];
//cronometro
void cronometro(){
  seconds = seconds + 1;
  if(seconds > 59){
    seconds = 0;
    minutes = minutes + 1;
  }
  if(minutes > 59){
    minutes = 0;
    hours = hours + 1;
  }
  Serial.println(String(hours) + ":" + String(minutes) + ":" + String(seconds));
  delay(1000);
}// fin cronometro

//metodo para limpiar cronometro
void clearCronometro(){
  seconds = 0;
  minutes = 0;
  hours = 0;
}// fin clearCronometro

//metodo para almacenar la totalidad del tiempo
void almacenamientoCronometro(int hours_total,int minutes_total,int seconds_total){
    arraytimeTotal[0]=arraytimeTotal[0]+hours_total;
    arraytimeTotal[1]=arraytimeTotal[1]+minutes_total;
    arraytimeTotal[2]=arraytimeTotal[2]+seconds_total; 
    if(arraytimeTotal[2] > 59){
      arraytimeTotal[2] = 0;
      arraytimeTotal[1] = arraytimeTotal[1]+1;          
    }
    if(arraytimeTotal[1] > 59){
      arraytimeTotal[1] = 0;
      arraytimeTotal[0] = arraytimeTotal[1]+1;    
    }
    } //fin almacenamientoCronometro
//-------------------------------------------------------------------------------------------------------------------
void setup() {
	Serial.begin(9600);
	pinMode(pin_tendedora,INPUT);
  	pinMode(pin_cortadora,INPUT);
  	pinMode(pin_recogido,INPUT);
}

void loop() {
      do{
        if(digitalRead(pin_tendedora)== HIGH){
          ver_recogido = true;
        }
      }while(ver_recogido == false);
      ver_recogido = false;

  //tendido
  while(ver_tendedora == false){
  	cronometro();
    if(digitalRead(pin_tendedora) == LOW){
      cont_tendedora = cont_tendedora + 1;
      delay(300);
      Serial.println(cont_tendedora);
      if(cont_tendedora == 10){
        ver_tendedora = true;
        alm_tendedora = alm_tendedora + String(hours)+":"+ String(minutes)+":"+ String(seconds);
        almacenamientoCronometro(hours, minutes,seconds);
        clearCronometro();
      }
    }
  }//fin tendido
    do{
        ver_tendedora = false;
        if(digitalRead(pin_cortadora)== HIGH){
          ver_tendedora = true;
        }
      }while(ver_tendedora == false);

  //cortadora
  while(ver_cortadora == false){
    cronometro();
    if(digitalRead(pin_cortadora) == LOW){
      cont_cortadora = cont_cortadora + 1;
      delay(300);
      if(cont_cortadora == 1){
        ver_cortadora = true;
        alm_cortadora = alm_cortadora + String(hours)+":"+ String(minutes)+":"+ String(seconds);
        almacenamientoCronometro(hours, minutes,seconds);
        clearCronometro();
    }
  }
}//fin cortadora

    do{
        ver_cortadora = false;
        if(digitalRead(pin_recogido)== HIGH){
          ver_cortadora = true;
        }
      }while(ver_cortadora == false);

//recogido
  while(ver_recogido == false){
    cronometro();
    if(digitalRead(pin_recogido) == LOW){
      cont_recogido = cont_recogido + 1;
      delay(300);
      if(cont_recogido == 2){
        ver_recogido = true;
        alm_recogido = alm_recogido + String(hours)+":"+ String(minutes)+":"+ String(seconds);
        almacenamientoCronometro(hours, minutes,seconds);
        clearCronometro();
    }
    }
  }//fin recogido
  alm_total  = alm_total + String(arraytimeTotal[0]) + ":" + String(arraytimeTotal[1]) + ":" + String(arraytimeTotal[2]);
  Serial.println("-------------------------------------------------------------------------------");
  Serial.println(alm_tendedora);
  Serial.println(alm_cortadora);
  Serial.println(alm_recogido);
  Serial.println(alm_total);
  Serial.println("-------------------------------------------------------------------------------");
  delay(60000);
}//fin loop