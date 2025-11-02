let imagenes=["pr1.png", "pr2.png", "pr3.png", "pr4.png", "pr5.png", "pr6.png", "pr7.png", "pr8.png"];
let ind=0;

const img1=document.getElementById("img1");
const img2=document.getElementById("img2");
const img3=document.getElementById("img3");


const btnant=document.getElementById("btnant");
const btnnxt=document.getElementById("btnnext");


function atras(){
    ind--;
    if(ind<0) ind=imagenes.length-1;
    img1.src=imagenes[(ind-1+imagenes.length)%imagenes.length];
    img2.src=imagenes[ind];
    img3.src=imagenes[(ind+1)%imagenes.length];
    console.log(ind);
}

function adelante(){
    ind++;
    ind%=imagenes.length;
    img1.src=imagenes[(ind-1+imagenes.length)%imagenes.length];
    img2.src=imagenes[ind];
    img3.src=imagenes[(ind+1)%imagenes.length];
    console.log(ind);
}