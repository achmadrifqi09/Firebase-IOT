import { initializeApp } from "https://www.gstatic.com/firebasejs/9.9.0/firebase-app.js";
import { getDatabase, get, child, ref } from "https://www.gstatic.com/firebasejs/9.9.0/firebase-database.js";

const config = initializeApp({
    apiKey: "AIzaSyDf4c_B5n2uFFgsTZtMEhCBN_ZsROIrv3E",
    authDomain: "data-db1b1.firebaseapp.com",
    databaseURL: "https://data-db1b1-default-rtdb.firebaseio.com",
    projectId: "data-db1b1",
    storageBucket: "data-db1b1.appspot.com",
    messagingSenderId: "1075045105437",
    appId: "1:1075045105437:web:d0e8e4a298a21f7ae2abf4"
});

const refDb = ref(getDatabase());
let listData = [];
get(child(refDb, 'data/')).then((snapshot) => {
    snapshotToArray(snapshot);
})

function snapshotToArray(snapshot) {
    snapshot.forEach(function(childSnapshot) {
        let childData = childSnapshot.val();
        listData.push(childData["suhu"])
    });

    let displayedData = [];

    if (listData.length <= 7) {
        displayedData = listData;
    } else {
        let startIndex = listData.length - 7;
        for (let i = startIndex; i < listData.length; i++) {
            displayedData.push(listData[i]);
        }
    }
    let labels = [1, 2, 3, 4, 5, 6, 7];

    const ctx = document.getElementById('myChart').getContext('2d');
    const data = {
        labels: labels,
        datasets: [{
            label: 'Suhu',
            data: displayedData,
            fill: false,
            borderColor: 'rgb(75, 192, 192)',
            tension: 0.1
        }]
    };
    const myChart = new Chart(ctx, {
        type: 'line',
        data: data,
        options: {
            responsive: true,
            plugins: {
                legend: {
                    display: false
                },
                title: {
                    display: false,
                    text: 'Chart.js Line Chart'
                }
            }
        },
    });

    const config = {
        type: 'line',
        data: data,
    };
}