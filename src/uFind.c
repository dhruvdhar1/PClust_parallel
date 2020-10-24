#include "uFind.h"
#include <omp.h>

struct ufind *init_union(int size) {
	int i;
	struct ufind *ufSet;
	ufSet = emalloc(size*sizeof(struct ufind));
	#pragma omp parallel for schedule(dynamic,150) shared(i) num_threads(2)
			for (i=0; i<size; i++)
			{
				//printf("\n Thread num %d",omp_get_thread_num());
				ufSet[i].parent = i;
				ufSet[i].rank = 0;
			}
	return ufSet;
}

void free_union(struct ufind *uf)
{
    free(uf);
}
int find(struct ufind *ufSet, int elemIndex)
{
		int myParent;
		myParent = ufSet[elemIndex].parent;
		if (ufSet[myParent].parent != myParent)
		{
				myParent = ufSet[elemIndex].parent = find(ufSet, myParent);
				ufSet[myParent].rank--;
				return myParent;
		}
		else
		{
				return myParent;
		}
}
 void union_elems(struct ufind *ufSet, int elem1, int elem2)
 {
    	merge_elems(ufSet, find(ufSet, elem1), find(ufSet, elem2));
 }
/* can never been called outside of this file */
 void merge_elems(struct ufind *ufSet, int elem1, int elem2)
 {
			if (elem1!=elem2)
			{
					if (ufSet[elem1].rank > ufSet[elem2].rank)
					{
								ufSet[elem2].parent = elem1;
					}
					else
					{
								ufSet[elem1].parent = elem2;
								if (ufSet[elem1].rank==ufSet[elem2].rank)
								{
										ufSet[elem2].rank++;
								}
					}
			}
}

int disp_all_clusters(struct ufind *uf, int size, int *singletons, char *dir)
{
		int clustcnt=0,Clust1cnt=0;
		int i=0, iClusters=0;
		struct clusters *clust;
		struct link *temp, *temp_fix;
		int root;
		char s[200];
		FILE *fp, *fp1, *fp2, *fp3;

		clust = emalloc(sizeof(struct clusters)*size);

		for (i=0; i<size; i++)
		{
				clust[i].count=1;
				clust[i].singleton='1';
				clust[i].head=NULL;
		}

		for (i=0; i<size; i++)
		{
				root = find(uf, i);
				if (i!=root)
				{
						temp = emalloc(sizeof(struct link));
						temp->id=i;
						temp->next=clust[root].head;
						clust[root].head=temp;
						clust[root].count++;
						clust[root].singleton='0';
						clust[i].singleton = '0';
						clust[i].head = NULL;
			}
		} /* end for */
		//printf("%s\n",dir );
		sprintf(s, "%s/outputFiles/vertexClustSize.%d.SGL", dir, size);
		fp1 = efopen(s, "w");
		fp2	= efopen("src/vertexCustomClustSize","w");
		fp3	= efopen("src/vertexDensity.SGL","w");
		//printf("SSSIze :%d\n",size );
		sprintf(s, "%s/outputFiles/vertexClust.%d.SGL", dir, size);
		fp = efopen(s, "w");
		iClusters=0;
		*singletons=0;
		for (i=0; i<size; i++)
		{
				if (clust[i].singleton=='0' && clust[i].head!=NULL)
				{
						fprintf(fp, "{Cluster#}   %d\n", iClusters);
						fprintf(fp, "{Member#}  %s\n", n2gidHash[i]+1);
						temp = clust[i].head;
						while (temp!=NULL)
						{
							fprintf(fp, "{Member#}  %s\n", n2gidHash[temp->id]+1);
							temp = temp->next;
						}
						fprintf(fp1, "%d %d\n", iClusters, clust[i].count);
						iClusters++;
						if(clust[i].count>1)
						{
								fprintf(fp2, "%d:%d\n", iClusters, clust[i].count);
								clustcnt++;
						}
						else
						{
								Clust1cnt++;
						}
				}
				else
				{
						if (clust[i].singleton=='1')
						{
							fprintf(fp, "{Cluster#}   %d\n", iClusters);
							fprintf(fp, "{Member#}  %s\n", n2gidHash[i]+1);
							fprintf(fp1, "%d %d\n", iClusters, clust[i].count);
							if(clust[i].count>1)
							{
									fprintf(fp2, "%d %d\n", iClusters, clust[i].count);
									clustcnt++;
							}
							else
							{
									Clust1cnt++;
							}
							iClusters++;
							(*singletons)++;
						}
				}
			} /* end for 2 */
			fclose(fp);
			fclose(fp1);
			fclose(fp2);
			for (i=0; i<size; i++)
			{
					if (clust[i].head)
					{
							temp = clust[i].head;
							while (temp->next != 0)
							{
									temp_fix = temp->next;
									free(temp);
									temp = temp_fix;
							}
							free(temp);
					}
			}
			//printf("%d clusters with more than 1 member %d\n",clustcnt ,Clust1cnt );
			fprintf(fp3, "%d:%d\n",clustcnt,Clust1cnt);
			fclose(fp3);
			if (clust)
					free(clust);
			return iClusters;
}
void disp(struct ufind *ufSet, int size)
{
		int i;
		for (i=0; i<size; i++)
		{
				if (i!=ufSet[i].parent)
				printf("(%d,%d) ", i, ufSet[i].parent);
				fflush(stdout);
		}
		printf("\n");
}

/* union two list as one cc */
void list_union(struct ufind *ufset, int *list1, int nlist1, int *list2, int nlist2)
{
    assert(nlist1 > 0 && nlist2 > 0);
    int base;
    int i;
    base = list1[0];
    for(i=1; i<nlist1; i++)
		{
      	union_elems(ufset, base, list1[i]);
    }
    for(i=0; i<nlist2; i++)
		{
        union_elems(ufset, base, list2[i]);
    }
}
