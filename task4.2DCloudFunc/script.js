// Get the three room controls from the HTML page
const livingRoom = document.getElementById("livingRoom");
const bathroom = document.getElementById("bathroom");
const closet = document.getElementById("closet");

// Send the selected room to the backend
async function sendRoom(room) {
    console.log("Sending room:", room);

    try {
        // Send the room name to our Node.js backend
        const response = await fetch("http://localhost:3000/toggle", {
            method: "POST",

            // Tell the backend that we are sending JSON data
            headers: {
                "Content-Type": "application/json"
            },

            // Convert the room name into JSON
            body: JSON.stringify({
                room: room
            })
        });

        // Get the response sent back by the backend
        const data = await response.json();

        // Show the backend response in the browser console
        console.log("Backend response:", data);
    }
    catch (error) {
        // Display an error if the backend cannot be reached
        console.log("Error connecting to backend:", error);
    }
}

// Run the function whenever the Living Room checkbox changes
livingRoom.addEventListener("change", function () {
    sendRoom("living room");
});

// Run the function whenever the Bathroom checkbox changes
bathroom.addEventListener("change", function () {
    sendRoom("bathroom");
});

// Run the function whenever the Closet checkbox changes
closet.addEventListener("change", function () {
    sendRoom("closet");
});