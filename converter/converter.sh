#!/bin/bash

# Vérifie si au moins un fichier est passé en argument
if [ $# -eq 0 ]; then
    echo "Usage: $0 file1.png file2.png ... fileN.png"
    exit 1
fi

# Boucle sur chaque argument (fichier PNG)
for png_file in "$@"; do
    # Vérifie si le fichier existe et est un fichier régulier
    if [ ! -f "$png_file" ]; then
        echo "Fichier $png_file non trouvé ou n'est pas un fichier régulier."
        continue
    fi

    # Récupère le nom du fichier sans l'extension
    base_name=$(basename "$png_file" .png)

    # Convertit le fichier PNG en XPM
    convert "$png_file" "${base_name}.xpm"

    # Vérifie si la conversion a réussi
    if [ $? -eq 0 ]; then
        echo "Conversion réussie: $png_file -> ${base_name}.xpm"
    else
        echo "Erreur lors de la conversion de $png_file."
    fi
done

