#pragma once
#include <string>
#include <vector>
#include <fstream> // Pour lire et écrire dans les fichiers

// Classe qui gère le chiffrement et le déchiffrement de fichiers
class NoyauChiffrement {
public:
    // Codes pour indiquer si tout s'est bien passé ou s'il y a eu une erreur
    enum class CodeErreur {
        OK,
        MotDePasseVide,
        ErreurLecture,
        ErreurEcriture
    };

    // Constructeur (ici il ne fait rien de spécial)
    NoyauChiffrement();

    // Fonction pour chiffrer un fichier
    CodeErreur chiffrerFichier(const std::string& cheminEntree, const std::string& cheminSortie, const std::string& motDePasse, std::string& messageErreur);

    // Fonction pour déchiffrer un fichier
    CodeErreur dechiffrerFichier(const std::string& cheminEntree, const std::string& cheminSortie, const std::string& motDePasse, std::string& messageErreur);

private:
    // Lis le contenu d'un fichier et le met dans un tableau
    std::vector<char> lireFichier(const std::string& chemin, std::string& messageErreur);

    // Écrit un tableau de données dans un fichier
    bool ecrireFichier(const std::string& chemin, const std::vector<char>& donnees, std::string& messageErreur);

    // Mélange les données avec le mot de passe (XOR)
    std::vector<char> melangerDonnees(const std::vector<char>& donnees, const std::string& motDePasse);

    // Crée une clé à partir du mot de passe pour le mélange
    std::vector<char> creerCle(const std::string& motDePasse, size_t taille);
};