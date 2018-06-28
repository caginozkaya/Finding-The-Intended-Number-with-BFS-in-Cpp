

#include <iostream>
#include <queue>
#include <vector>


using namespace std;


int swap(int convert, int process[2]) { //basamak degisimi icin fonksiyon

	int arr[4], i, temp, result, index1, index2;
	index1 = process[0];
	index2 = process[1];


	for (i = 0; i < 4; i++) {
		arr[3 - i] = convert % 10;
		convert /= 10;
	}

	temp = arr[index1];
	arr[index1] = arr[index2];
	arr[index2] = temp;

	result = arr[0] * 1000 + arr[1] * 100 + arr[2] * 10 + arr[3];

	return result;
}

int main() {

	int query, target = 1234, left[2] = { 0,1 }, middle[2] = { 1,2 }, right[2] = { 2,3 };
	int comp1, comp2, comp3, step = 0, i = 0, j = 0, parent = 1, parentT;
	bool c1 = true, c2 = true, c3 = true;


	queue<int> open;//BFS icin tutulan queue, bir dugum acildiginda acilan degerleri tutar
					//bir dugumun butun cocuklari acildiginda o dugum queue'dan silinir

	vector<int> closed;//agaca eklenen her bir degeri tutar

	vector<int> values;//parents vektorundeki degerlerle ikiskili degerler
					   //dongu testini gecen ve closed'a eklenecek degerler

	vector<int> parents;// values vektorundeki degerlere iliskin parent degerleri:
						//parents vektoru, bir degerin hangi degerden geldigi bilgisini tutar

	vector<int> control1;//o an eklenecek olan dugumun dongu kontrolu icin olusturulan vektor
						 //eklenecek dugumden parent parent yukari cikilarak ata parent'a kadar olan degerleri icerir
						 //swap left icin

	vector<int> control2;//swap middle icin
	vector<int> control3;//swap right icin


	cout << "Enter the starting number: " << endl;
	cin >> query;

	open.push(query);//baslangic adimi


	values.push_back(query);//baslangic adimi

	parents.push_back(0);// ata parent 

	closed.push_back(0);//baslangic adimi

	closed.push_back(query);//baslangic adimi


	while (true) {

		if (open.front() == target)//target kontrolu
			break;

		//**********************swap left islemi****************************

		comp1 = swap(open.front(), left);//queue'dan al, basamak islemini yap

		parentT = parent;//ana while(true) dongusunun bu adimda acilacak olan dugumlerin parent degerini degistirmemek icin islemlerde kullanilacak
						 //gecici parent degeri

		values.push_back(comp1);//dongu yok kabul et ve degeri ekle
		parents.push_back(parent);//dongu yok kabul et ve degerin parent'ini ekle

		while (parentT != 0) {//ata parent'a ulasilana kadar


			control1.push_back(values[parentT - 1]);//suanki dugumun parent'ini kontrole ekle
			parentT = parents[parentT - 1];//parentT'nin yeni degerini suanki parent'in parent'i yap


		}

		for (i = 0; i < control1.size(); i++)//ataya kadar kontrol et
			if (comp1 == control1[i])
				c1 = false;//dongu varsa false dondur


		if (c1) {//dongu yoksa 
			open.push(comp1);//actigin cocugu queue'ya ekle
			closed.push_back(comp1);//agaca ekle
			step++;//adim sayisini 1 arttir
		}
		else {//dongu varsa
			values.pop_back();//daha once dongu yok diye kabul edip ekledigin degeri geri sil
			parents.pop_back();//daha once dongu yok diye kabul edip ekledigin degeri geri sil

		}


		if (comp1 == target)//target kontrolu
			break;

		//*********************swap middle ve swap right islemleri icin tekrarla*******************

		comp2 = swap(open.front(), middle);

		parentT = parent;

		values.push_back(comp2);
		parents.push_back(parent);

		while (parentT != 0) {


			control2.push_back(values[parentT - 1]);
			parentT = parents[parentT - 1];

		}

		for (i = 0; i < control2.size(); i++)
			if (comp2 == control2[i])
				c2 = false;


		if (c2) {
			open.push(comp2);
			closed.push_back(comp2);
			step++;
		}
		else {
			values.pop_back();
			parents.pop_back();

		}


		if (comp2 == target)//target kontrolu
			break;

		comp3 = swap(open.front(), right);

		parentT = parent;

		values.push_back(comp3);
		parents.push_back(parent);


		while (parentT != 0) {


			control3.push_back(values[parentT - 1]);
			parentT = parents[parentT - 1];


		}

		for (i = 0; i < control3.size(); i++)
			if (comp3 == control3[i])
				c3 = false;


		if (c3) {
			open.push(comp3);
			closed.push_back(comp3);
			step++;
		}
		else {
			values.pop_back();
			parents.pop_back();

		}

		if (comp3 == target)//target kontrolu
			break;



		open.pop();//cocuklarini actigin dugumu at, bir sonraki queue elemanina gecilmesini sagla
				   //(agacta yatay ilerlenmesini sagla)

		parent++;//suanki acilan dugumun islemleri bitince yeni dugume gecildiginde yeni parent degerine sahip olmasini sagla

		control1.clear();//kontrol vektorlerini temizle
		control2.clear();
		control3.clear();

		c1 = true;//dongu olmadigi surece true
		c2 = true;
		c3 = true;

	}




	for (i = 1; i<closed.size(); i++)
		cout << closed[i] << " -> ";

	cout << "TARGET" << endl;
	cout << "Target has been reached at step " << step << "." << endl;



	cout << endl;
	system("pause");

	return 0;


}