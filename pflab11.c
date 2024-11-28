#include <stdio.h>
#include <string.h>

struct player
{
    char name[20];
    char team[20];
};

struct bowl
{
    char type[10];
    char arm[5];
    struct player ply;
};

struct bat
{
    char type[10];
    char handed[8];
    struct bowl ply2;
};

void create_player(FILE *file, struct player p);
void read_players(FILE *file);
void update_player(FILE *file, int position, struct player updated_player);
void delete_player(FILE *file, int position);

void create_bowl(FILE *file, struct bowl b);
void read_bowls(FILE *file);
void update_bowl(FILE *file, int position, struct bowl updated_bowl);
void delete_bowl(FILE *file, int position);

void create_bat(FILE *file, struct bat b);
void read_bats(FILE *file);
void update_bat(FILE *file, int position, struct bat updated_bat);
void delete_bat(FILE *file, int position);

int main()
{
    FILE *file;

    struct player p1 = {"John", "Team A"};
    struct player p2 = {"Mark", "Team B"};

    struct bowl b1 = {"pacer", "right", p1};
    struct bowl b2 = {"spinner", "left", p2};

    struct bat bat1 = {"top order", "lefty", b1};
    struct bat bat2 = {"middle order", "righty", b2};

    file = fopen("players.dat", "rb+");
    if (file == NULL)
    {
        file = fopen("players.dat", "wb+");
    }

    create_player(file, p1);
    create_player(file, p2);

    fclose(file);
    file = fopen("bowls.dat", "rb+");
    if (file == NULL)
    {
        file = fopen("bowls.dat", "wb+");
    }

    create_bowl(file, b1);
    create_bowl(file, b2);

    fclose(file);
    file = fopen("bats.dat", "rb+");
    if (file == NULL)
    {
        file = fopen("bats.dat", "wb+");
    }

    create_bat(file, bat1);
    create_bat(file, bat2);

    read_players(file);
    read_bowls(file);
    read_bats(file);

    
    struct bat updated_bat = {"lower order", "righty", b2};
    update_bat(file, 1, updated_bat);
    delete_bat(file, 0);

    read_bats(file);

    fclose(file);
    return 0;
}

void create_player(FILE *file, struct player p)
{
    fseek(file, 0, SEEK_END);
    fwrite(&p, sizeof(struct player), 1, file);
}

void read_players(FILE *file)
{
    struct player p;
    fseek(file, 0, SEEK_SET);
    while (fread(&p, sizeof(struct player), 1, file))
    {
        printf("Player: %s, Team: %s\n", p.name, p.team);
    }
    printf("\n");
}

void update_player(FILE *file, int position, struct player updated_player)
{
    fseek(file, position * sizeof(struct player), SEEK_SET);
    fwrite(&updated_player, sizeof(struct player), 1, file);
}

void delete_player(FILE *file, int position)
{
    FILE *tempFile = fopen("temp.dat", "wb");
    struct player p;
    fseek(file, 0, SEEK_SET);
    int currentPosition = 0;

    while (fread(&p, sizeof(struct player), 1, file))
    {
        if (currentPosition != position)
        {
            fwrite(&p, sizeof(struct player), 1, tempFile);
        }
        currentPosition++;
    }

    fclose(file);
    fclose(tempFile);
    remove("players.dat");
    rename("temp.dat", "players.dat");
}

// CRUD for Bowl
void create_bowl(FILE *file, struct bowl b)
{
    fseek(file, 0, SEEK_END);
    fwrite(&b, sizeof(struct bowl), 1, file);
}

void read_bowls(FILE *file)
{
    struct bowl b;
    fseek(file, 0, SEEK_SET);
    while (fread(&b, sizeof(struct bowl), 1, file))
    {
        printf("Bowler Type: %s, Arm: %s, Player: %s, Team: %s\n", b.type, b.arm, b.ply.name, b.ply.team);
    }
    printf("\n");
}

void update_bowl(FILE *file, int position, struct bowl updated_bowl)
{
    fseek(file, position * sizeof(struct bowl), SEEK_SET);
    fwrite(&updated_bowl, sizeof(struct bowl), 1, file);
}

void delete_bowl(FILE *file, int position)
{
    FILE *tempFile = fopen("temp.dat", "wb");
    struct bowl b;
    fseek(file, 0, SEEK_SET);
    int currentPosition = 0;

    while (fread(&b, sizeof(struct bowl), 1, file))
    {
        if (currentPosition != position)
        {
            fwrite(&b, sizeof(struct bowl), 1, tempFile);
        }
        currentPosition++;
    }

    fclose(file);
    fclose(tempFile);
    remove("bowls.dat");
    rename("temp.dat", "bowls.dat");
}


void create_bat(FILE *file, struct bat b)
{
    fseek(file, 0, SEEK_END);
    fwrite(&b, sizeof(struct bat), 1, file);
}

void read_bats(FILE *file)
{
    struct bat b;
    fseek(file, 0, SEEK_SET);
    while (fread(&b, sizeof(struct bat), 1, file))
    {
        printf("Bat Type: %s, Handed: %s, Bowler Type: %s, Arm: %s, Player: %s, Team: %s\n",
               b.type, b.handed, b.ply2.type, b.ply2.arm, b.ply2.ply.name, b.ply2.ply.team);
    }
    printf("\n");
}

void update_bat(FILE *file, int position, struct bat updated_bat)
{
    fseek(file, position * sizeof(struct bat), SEEK_SET);
    fwrite(&updated_bat, sizeof(struct bat), 1, file);
}

void delete_bat(FILE *file, int position)
{
    FILE *tempFile = fopen("temp.dat", "wb");
    struct bat b;
    fseek(file, 0, SEEK_SET);
    int currentPosition = 0;

    while (fread(&b, sizeof(struct bat), 1, file))
    {
        if (currentPosition != position)
        {
            fwrite(&b, sizeof(struct bat), 1, tempFile);
        }
        currentPosition++;
    }

    fclose(file);
    fclose(tempFile);
    remove("bats.dat");
    rename("temp.dat", "bats.dat");
}
