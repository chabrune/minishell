# Minishell - Un shell simple mais puissant

Un projet de création d'un shell basique inspiré de bash, implémentant les fonctionnalités essentielles d'un interpréteur de commandes.

## 📝 Description

Minishell est un shell interactif qui permet d'exécuter des commandes, gérer des variables d'environnement, et effectuer des redirections et des pipes.

## 🛠️ Fonctionnalités

- Affichage d'un prompt
- Historique des commandes
- Exécution de commandes (via PATH ou chemins absolus/relatifs)
- Gestion des guillemets simples et doubles
- Redirections (<, >, <<, >>)
- Pipes (|)
- Variables d'environnement ($VAR)
- Gestion du statut de sortie ($?)
- Gestion des signaux (ctrl-C, ctrl-D, ctrl-$$

### Builtins implémentés
- echo (avec option -n)
- cd
- pwd
- export
- unset
- env
- exit

## ⚠️ Gestion d'erreurs
- Pas d'interprétation des quotes non fermées
- Gestion appropriée des caractères spéciaux

## 📚 Fonctions externes autorisées
readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history, printf, malloc, free, write, access, open, read, close, fork, wait, waitpid, wait3, wait4, signal, sigaction, sigemptyset, sigaddset, kill, exit, getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, perror, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

---
*Projet réalisé dans le cadre du cursus de l'école 42*
