$executablePath = "C:\Users\Cosmin\Desktop\CUDA\cmake-build-debug\CUDA.exe" # Modifică aici cu calea executabilului
$param2 = 4
$param3 = 10

$suma = 0

for ($i = 0; $i -lt $param3; $i++) {
    Write-Host "Rulare #$($i+1)"

    $a = (cmd /c "`"$executablePath`" $param2 2`>`&1").Trim()

    if ($a -match "^\d+(\.\d+)?$") {
        $execTime = [double]::Parse($a, [System.Globalization.CultureInfo]::InvariantCulture)
        Write-Host "Timp de executie: $execTime ms"
        $suma += $execTime
    } else {
        Write-Error "Ieșirea nu este un număr valid: $a"
        continue
    }

    Write-Host ""
}

# Calcul mediu
$media = $suma / $param3
Write-Host "Timp de execuție mediu: $media"

# Creare fișier .csv
if (!(Test-Path outC.csv)) {
    New-Item outC.csv -ItemType File
    # Scrie date în csv
    Set-Content outC.csv 'Tip Matrice,Tip alocare,Nr threads,Timp execuție'
}

# Append date în fișierul CSV
Add-Content outC.csv ",,$param2,$media"
