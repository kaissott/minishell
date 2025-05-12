# Utilise Debian stable (compatible M1/M2 via Docker)
FROM debian:bullseye

# Installe les outils nécessaires
RUN apt update && \
    apt install -y gcc make valgrind bash libreadline-dev

# Dossier de travail dans le conteneur
WORKDIR /mnt

# Lance bash par défaut quand on exécute le conteneur
CMD ["/bin/bash"]
