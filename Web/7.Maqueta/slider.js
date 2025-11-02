let imagenes=["img/pr1.png", "img/pr2.png", "img/pr3.png", "img/pr4.png", "img/pr5.png", "img/pr6.png", "img/pr7.png", "img/pr8.png"];
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