#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#pragma warning (disable: 4996)

typedef struct _BTnode {
	short datum_bit;//�x�s���O: �O0�٬O1? �u����إi��C
	int ID;//ID�N���D�ؤ��ҵ����s���C�p�G�o��BTnode��ڤW�OOR�A�x�s0�C�p�G��ڤW�OAND�A�x�s-1�C
	struct _BTnode *leftchild;
	struct _BTnode *rightchild;
	struct _BTnode *parent;
}BTNode;


BTNode *TreeConstruction(BTNode **, BTNode *);
void flip(BTNode *);
void TreeDestruction(BTNode *);

BTNode *true_root = NULL;//�����u����root����m�C�o�ӬO��flip�禡�ϥΡA�_�hflip�i��|�~���true_root��parent��flip�A�y��runtime error�C


int main() {
	int T; scanf("%d", &T);
	while (T--) {
		int N, M; scanf("%d%d", &N, &M);
		BTNode **ID = (BTNode **)malloc(sizeof(BTNode)*N);//�x�sID=0~ID=N-1��node�����Ц�m

		/*BTNode fake_head;//fake_head�O�u����root��parent�A�ҥHfake_head��child�O�u����root�C
		fake_head.leftchild= TreeConstruction(ID, &fake_head);//(1)Ū�JBoolean func�A�ç�Ҧ�node��datum_bit�]�w��0�A�]�@�֧�ID=0��node~ID=N-1��node �� ��m�A�x�s�b�@��pointer�}�C�̡C(2)�]���u���@��child�A�ڴN�H�K�D�F���䪺�ӥΡC
		true_root = fake_head.leftchild;*/
		true_root = TreeConstruction(ID, true_root);


		while (M--) {
			//Ū�J�nflip��ID�A����I�sfunction��Ҧ��|�Q�s�a�v�T��parent��datum_bit����F�C
			int goal_ID; scanf("%d", &goal_ID);
			flip(ID[goal_ID]);

			//�����Xsyntax tree �`root��datum_bit�A�O�o\n
			printf("%hd\n", true_root->datum_bit);
		}

		TreeDestruction(true_root);
	}

	system("pause");
}

//Ū�JBoolean func(infix���A�A�Yroot-left-right)�A�ç�Ҧ�node��datum_bit�]�w��0�A
//�]�@�֧�ID=0��node~ID=N-1��node �� ��m�A�x�s�b�@��pointer�}�C�̡C
BTNode *TreeConstruction(BTNode **ID, BTNode *parent) {
	int num_in;
	char c; while (isspace(c = getchar()))continue;
	BTNode *root = NULL;

	if (c == '[') {
		scanf("%d]", &num_in);

		root = (BTNode *)malloc(sizeof(BTNode));

		root->datum_bit = 0;
		root->ID = num_in;
		root->parent = parent;
		root->leftchild = root->rightchild = NULL;

		ID[num_in] = root;

		return root;
	}
	else {
		root = (BTNode *)malloc(sizeof(BTNode));

		root->datum_bit = 0;
		root->ID = (c == '|') ? 0 : -1;
		root->parent = parent;
		root->leftchild = TreeConstruction(ID, root);
		root->rightchild = TreeConstruction(ID, root);

		return root;
	}

}


//Ū�J�nflip��ID�A����I�sfunction��Ҧ��|�Q�s�a�v�T��parent��datum_bit����F�C
void flip(BTNode *the_flipped) {

	if (the_flipped->ID != 0 && the_flipped->ID != -1) {
		the_flipped->datum_bit = !(the_flipped->datum_bit);

		if (the_flipped != true_root)flip(the_flipped->parent);
	}
	else if (the_flipped->ID == 0) {//�N��o��node�OOR
		int original_datum_bit = the_flipped->datum_bit;
		the_flipped->datum_bit = the_flipped->leftchild->datum_bit | the_flipped->rightchild->datum_bit;

		if (original_datum_bit == the_flipped->datum_bit)return;//�p�G���s�p��᪺���G�M�쥻�@�ˡA���᭱�@�w���|�O���ۦP�A�N���Χ�F�C
		else {
			if (the_flipped != true_root)flip(the_flipped->parent);
		}

	}
	else if (the_flipped->ID == -1) {//�N��o��node�OAND
		int original_datum_bit = the_flipped->datum_bit;
		the_flipped->datum_bit = the_flipped->leftchild->datum_bit & the_flipped->rightchild->datum_bit;

		if (original_datum_bit == the_flipped->datum_bit)return;//�p�G���s�p��᪺���G�M�쥻�@�ˡA���᭱�@�w���|�O���ۦP�A�N���Χ�F�C
		else {
			if (the_flipped != true_root)flip(the_flipped->parent);
		}
	}

}

void TreeDestruction(BTNode *root) {
	if (root != NULL) {
		TreeDestruction(root->leftchild);
		TreeDestruction(root->rightchild);

		free(root);
	}
}