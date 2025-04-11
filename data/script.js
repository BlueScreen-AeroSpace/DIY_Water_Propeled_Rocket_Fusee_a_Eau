let donnees = [
    {
        "id": 0,
        "name": "Humidité",
        "state": true,
        "capteur": "BME280"
    },
    {
        "id": 1,
        "name": "Température",
        "state": true,
        "capteur": "BME280"
    },
    {
        "id": 2,
        "name": "Pression atmosphérique",
        "state": true,
        "capteur": "BME280"
    },
    {
        "id": 3,
        "name": "Accélération",
        "state": true,
        "capteur": "ADXL345"
    },
    {
        "id": 4,
        "name": "Date",
        "state": true,
        "capteur": "DS1307Clock"
    },
    {
        "id": 5,
        "name": "Heure",
        "state": true,
        "capteur": "DS1307Clock"
    }
]

let capteurs = [
    {
        "id": 0,
        "name": "BME280",
        "state": true,
        "message": "*Obligatoire"
    },
    {
        "id": 1,
        "name": "ADXL345",
        "state": true,
        "message": ""
    },
    {
        "id": 2,
        "name": "DS1307Clock",
        "state": true,
        "message": ""
    }
]

let dateActuelle = new Date();

let anneeActuelle = dateActuelle.getFullYear();
let moisActuel = String(dateActuelle.getMonth() + 1).padStart(2, '0');
let jourActuel = String(dateActuelle.getDate()).padStart(2, '0');
let heureActuelle = String(dateActuelle.getHours()).padStart(2, '0');
let minuteActuelle = String(dateActuelle.getMinutes()).padStart(2, '0');
let secondeActuelle = String(dateActuelle.getSeconds()).padStart(2, '0');

let dateEtHeureActuelleString = `${anneeActuelle}-${moisActuel}-${jourActuel}T${heureActuelle}:${minuteActuelle}:${secondeActuelle}`;

function afficherCapteurs() {

    const list = document.getElementById("capteurs-list");
    list.innerHTML = "";
    capteurs.map(capteur => {

        const isDisabled = capteur.name === "BME280" ? "disabled" : "";

        const div = document.createElement("div");
        div.className = "capteur d-flex flex-row align-items-center gap-3";

        div.innerHTML = `
            <div class="d-flex flex-row align-items-center gap-2">
                <input type="checkbox" class="btn-check" id="checkbox${capteur.id}" 
                    ${capteur.state ? 'checked' : ''} ${isDisabled}
                    onchange="toggleCapteur(${capteur.id}, this)">
                <label class="btn btn-outline-primary px-3 text-nowrap" style="min-width: 125px;" for="checkbox${capteur.id}">
                    ${capteur.name}
                </label>
            </div>
            <p class="message mb-0 text-start" style="min-width: 100px; max-width: 100px;">${capteur.message}</p>`;

        list.appendChild(div);
    });
}

function hideCapteurs() {
    document.getElementById("donnees-div").style.display = "block";
    document.getElementById("capteurs-div").style.display = "none";
}

function toggleCapteur(id, checkbox) {
    let capteur = capteurs.find(c => c.id === id);
    if (capteur) {
        capteur.state = checkbox.checked;
    }
}

function afficherDonnees() {
    const list = document.getElementById("donnees-list");
    list.innerHTML = "";

    const capteursActifs = capteurs.filter(c => c.state).map(c => c.name);

    donnees.filter(d => capteursActifs.includes(d.capteur)).map(donnee => {
        const div = document.createElement("div");
        div.className = "donnee d-flex flex-column align-items-center";
        div.innerHTML = `
            <input type="checkbox" class="btn-check" id="checkbox-data${donnee.id}" 
                ${donnee.state ? 'checked' : ''}
                onchange="toggleDonnee(${donnee.id}, this)">
            <label class="btn btn-outline-primary" style="min-width: 200px;" for="checkbox-data${donnee.id}">
                ${donnee.name}
            </label>`;
        list.appendChild(div);
    });

    document.getElementById("capteurs-div").style.display = "none";
    document.getElementById("donnees-div").style.display = "block";
}

function hideDonnees() {
    document.getElementById("donnees-div").style.display = "none";
    document.getElementById("capteurs-div").style.display = "block";
}

function toggleDonnee(id, checkbox) {
    let donnee = donnees.find(d => d.id === id);
    if (donnee) {
        donnee.state = checkbox.checked;
    }
}

async function postData() {

    const capteursActifs = capteurs
        .filter(c => c.state)
        .map(c => c.name);

    const donneesActives = donnees
        .filter(d => d.state && capteursActifs.includes(d.capteur))
        .map(d => d.name);


    const payload = {
        capteurs: capteursActifs,
        donnees: donneesActives,
        dateEtHeure: dateEtHeureActuelleString

    };

    console.log("Données envoyées :", payload);


    fetch("http://192.168.4.1/api/config", {
        method: "POST",
        headers: {
            "Content-Type": "application/json"
        },
        body: JSON.stringify(payload)
    })
        .then(response => response.json())
        .then(data => {
            console.log("Réponse du serveur :", data);
            alert("Données enregistrées avec succès !");
        })
        .catch(error => {
            console.error("Erreur lors de l'envoi :", error);
            alert("Échec de l'enregistrement.");
        });
}

document.addEventListener("DOMContentLoaded", function () {
    afficherCapteurs();
})