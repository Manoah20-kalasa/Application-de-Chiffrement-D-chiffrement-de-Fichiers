#include "include/NoyauChiffrement.h"

// Constructeur vide
NoyauChiffrement::NoyauChiffrement() {}

// Fonction pour chiffrer un fichier
NoyauChiffrement::CodeErreur NoyauChiffrement::chiffrerFichier(const std::string& cheminEntree, const std::string& cheminSortie, const std::string& motDePasse, std::string& messageErreur) {
    if (motDePasse.empty()) {
        messageErreur = "Le mot de passe est vide.";
        return CodeErreur::MotDePasseVide;
    }
    // Lis le fichier à chiffrer
    std::vector<char> donnees = lireFichier(cheminEntree, messageErreur);
    if (!messageErreur.empty()) {
        return CodeErreur::ErreurLecture;
    }
    // Mélange les données avec le mot de passe
    std::vector<char> donneesChiffrees = melangerDonnees(donnees, motDePasse);
    // Écrit le résultat dans le fichier de sortie
    if (!ecrireFichier(cheminSortie, donneesChiffrees, messageErreur)) {
        return CodeErreur::ErreurEcriture;
    }
    return CodeErreur::OK;
}

// Fonction pour déchiffrer un fichier (même principe que chiffrer)
NoyauChiffrement::CodeErreur NoyauChiffrement::dechiffrerFichier(const std::string& cheminEntree, const std::string& cheminSortie, const std::string& motDePasse, std::string& messageErreur) {
    if (motDePasse.empty()) {
        messageErreur = "Le mot de passe est vide.";
        return CodeErreur::MotDePasseVide;
    }
    std::vector<char> donnees = lireFichier(cheminEntree, messageErreur);
    if (!messageErreur.empty()) {
        return CodeErreur::ErreurLecture;
    }
    std::vector<char> donneesDechiffrees = melangerDonnees(donnees, motDePasse);
    if (!ecrireFichier(cheminSortie, donneesDechiffrees, messageErreur)) {
        return CodeErreur::ErreurEcriture;
    }
    return CodeErreur::OK;
}

// Lis le contenu d'un fichier
std::vector<char> NoyauChiffrement::lireFichier(const std::string& chemin, std::string& messageErreur) {
    std::ifstream fichier(chemin, std::ios::binary);
    if (!fichier) {
        messageErreur = "Impossible d'ouvrir le fichier : " + chemin;
        return {};
    }
    std::vector<char> tampon((std::istreambuf_iterator<char>(fichier)), std::istreambuf_iterator<char>());
    if (fichier.bad()) {
        messageErreur = "Erreur de lecture du fichier : " + chemin;
        return {};
    }
    messageErreur.clear();
    return tampon;
}

// Écrit des données dans un fichier
bool NoyauChiffrement::ecrireFichier(const std::string& chemin, const std::vector<char>& donnees, std::string& messageErreur) {
    std::ofstream fichier(chemin, std::ios::binary);
    if (!fichier) {
        messageErreur = "Impossible d'ouvrir le fichier en écriture : " + chemin;
        return false;
    }
    fichier.write(donnees.data(), donnees.size());
    if (!fichier) {
        messageErreur = "Erreur d'écriture dans le fichier : " + chemin;
        return false;
    }
    messageErreur.clear();
    return true;
}

// Mélange les données avec la clé (XOR)
std::vector<char> NoyauChiffrement::melangerDonnees(const std::vector<char>& donnees, const std::string& motDePasse) {
    std::vector<char> cle = creerCle(motDePasse, donnees.size());
    std::vector<char> resultat(donnees.size());
    for (size_t i = 0; i < donnees.size(); ++i) {
        resultat[i] = donnees[i] ^ cle[i]; // Mélange chaque caractère avec la clé
    }
    return resultat;
}

// Crée une clé répétée à partir du mot de passe
std::vector<char> NoyauChiffrement::creerCle(const std::string& motDePasse, size_t taille) {
    std::vector<char> cle(taille);
    size_t tailleMotDePasse = motDePasse.size();
    for (size_t i = 0; i < taille; ++i) {
        cle[i] = motDePasse[i % tailleMotDePasse]; // Répète le mot de passe si besoin
    }
    return cle;
}