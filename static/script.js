function refresh() {
    $.get("RollsLeft", function(data) {
        document.getElementById("rolls").innerHTML = "Rolls Left: " + data;
    });

    $.get("BackendCheck", function(data) {
        document.getElementById("status").innerHTML = "Status: " + data;
    });
}