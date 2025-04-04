async function fetchCapteurs() {
    try {
        let response = await fetch('http://192.168.4.1/api/sensors', {
            method: 'GET',
            mode: 'cors'
        });

        if (!response.ok) throw new Error("Erreur lors de la récupération des capteurs");

        let textData = await response.text();

        let data = JSON.parse(textData);

        return data;

    } catch (error) {
        console.error("Erreur :", error);
    }
}

async function afficherCapteurs() {
    let capteurs = await fetchCapteurs();

    const list = document.getElementById("capteurs-list");
    list.innerHTML = "";
    capteurs.map(capteur => {
        const div = document.createElement("div");
        div.className = "capteur d-flex flex-column align-items-center";
        div.innerHTML = `
        <input type="checkbox" class="btn-check" id="checkbox${capteur.id}" 
            ${capteur.state ? 'checked' : ''} 
            onchange="toggleCapteur(${capteur.id}, this)">
        <label class="btn btn-outline-primary" for="checkbox${capteur.id}">${capteur.name}</label>`;
        list.appendChild(div);
    });
}

async function toggleCapteur(id, checkbox) {
    let newState = checkbox.checked;

    try {
        let response = await fetch("http://192.168.4.1/api/sensors", {
            method: "PUT",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify({ id, state: newState })
        });

        if (!response.ok) throw new Error("Erreur lors de la mise à jour du capteur");

        console.log(`Capteur ${id} mis à jour : ${newState}`);

    } catch (error) {
        console.error("Erreur :", error);
        checkbox.checked = !newState;
    }
}

document.addEventListener("DOMContentLoaded", function () {
    afficherCapteurs();
})