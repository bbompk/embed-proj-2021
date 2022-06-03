import { getDatabase,ref,onValue,update,get,set } from "https://www.gstatic.com/firebasejs/9.6.11/firebase-database.js";
// Import the functions you need from the SDKs you need
import { initializeApp } from "https://www.gstatic.com/firebasejs/9.6.11/firebase-app.js";
// TODO: Add SDKs for Firebase products that you want to use
// https://firebase.google.com/docs/web/setup#available-libraries

// Your web app's Firebase configuration
const firebaseConfig = {
  apiKey: "AIzaSyBD9cGi8zx1ZsuE2lIbvvB5Xwjlh451nyQ",
  authDomain: "emb-proj.firebaseapp.com",
  databaseURL: "https://emb-proj-default-rtdb.firebaseio.com",
  projectId: "emb-proj",
  storageBucket: "emb-proj.appspot.com",
  messagingSenderId: "16856658536",
  appId: "1:16856658536:web:1da83487fb883f5b3e81dd"
};

// Initialize Firebase
const app = initializeApp(firebaseConfig);
const db = getDatabase(app);


async function reset_data(){
  try {
    set(ref(db, "/"),{
          "people" : 0
     });
    console.log("reset");

  } catch (error) {
    console.log(error);
  }   
}


function click_reset(){
  reset_data();
}

let btn = document.getElementById("reset-btn")
btn.onclick = click_reset;

let people_count = document.getElementById("people-count");
const people_count_ref = ref(db, "people");
onValue(people_count_ref, (snapshot) => {
    people_count.innerHTML = Math.floor((snapshot.val()+1)/2);
});