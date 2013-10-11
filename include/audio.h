#ifndef AUIDO_CABECALHO_H
#define AUIDO_CABECALHO_H

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <string>

using namespace std;

#define FREQUENCIA 44100 
#define NUM_CANAIS 2
#define SIZE_SAMPLE 4096


class Audio
{
private:
	//audioSpec obtido da inicialização do SDL_OpenAudio
	static SDL_AudioSpec *audio_spec_obtido;
	//buffer da musica, que alimenta o controlador da placa
	static Uint8 *bufferAudio;
	//tamanho do buffer que alimenta a controladora da placa
	static int size;
	//posição no buffer em que o cursosr da musica está
	static int position;
	//booleano que diz se há algo tocando ou não
	static bool isPlaying;
	// Volume Áudio
	static int volume, volumeAntigo;
	static int volumeMixado;
	static string teste;	
public:
	//inicializa o SDL Audio
	static void init();
	//Alimenta o controlador da placa de audio com blocos de dados de tempos em tempos. Deve carregar as novas amostras quando solicitado, mixar o som no buffer e atualizar a posição do playback
	static void callback(void *userdata, Uint8 *stream, int len);
	//realiza todo o processo de carregar a musica especificada e trabalhá-la para que possa ser tocada
	static void setAudio(string nome_audio);
	//para a execução do áudio corrente e libera a memória da musica
	static void stopAudio();
	static void closeAudio();
	static void setVolume(int volumeRecebido);
	static int getVolume();
	static void pausaMusica();
	static void aumentaVolume();
	static void abaixaVolume();
	static void mute(bool estado);
};

#endif
