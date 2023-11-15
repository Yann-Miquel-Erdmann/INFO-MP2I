// remplit les n + 1 premières case de u telles que u[i] est la somme des i premières cases de t
void somme(float *t, float* u, int n){
    float s = 0;
    for (int i = 0; i < n+1; i++){
        u[i] = s;
        s+= t[i];
    }
}

void main(){
    float t[6] = {2.2,3.3,5.4,1.5,-3.6,3.7};
    float u[7];
    somme(t,u,6);
}