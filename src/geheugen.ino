
int geheugen_lichtkleur = 0;
int geheugen_lichtfelheid = 0;
int geheugen_geluid = 0;
float geheugen_temperatuur = 0;
int geheugen_co2 = 0;
int geheugen_luchtvochtigheid = 0;
int geheugen_gevoelsTemperatuur = 0;

bool geheugen_enabled = true;

inline void geheugen_enable(){
  geheugen_enabled = true;
}

inline void geheugen_disable(){
  geheugen_enabled = false;
}

void geheugen_set_lichtkleur(int val){
  if (geheugen_enabled){
    geheugen_lichtkleur = val;
  }
}

void geheugen_set_lichtfelheid(int val){
  if (geheugen_enabled){
    geheugen_lichtfelheid = val;
  }
}

void geheugen_set_geluid(int val){
  if (geheugen_enabled){
    geheugen_geluid = val;
  }
}

void geheugen_set_temperatuur(float val){
  if (geheugen_enabled){
    geheugen_temperatuur = val;
  }
}

void geheugen_set_co2(int val){
  if (geheugen_enabled){
    geheugen_co2 = val;
  }
}

void geheugen_set_luchtvochtgeid(int val){
  if (geheugen_enabled){
    geheugen_luchtvochtigheid = val;
  }
}
