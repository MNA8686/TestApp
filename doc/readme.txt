EquinoxDevelopment TestApp Ver.C95

■ このアプリについて

  思うところあってZen-Ichiのプログラムを組み直すことになった。
  これはZen-Ichiを動かすために新たに構築したシステムのテストプログラムである。
  本来はサークル内部向けであるが、C95バージョンとして特別公開する。

  2004年リリースのZen-Ichiからの変更点
    ・フルスクラッチ → バックエンドをSDLに
    ・ソフト描画 → 完全OpenGL化

    ゲームエンジンが台頭する中、何周遅れかという内容ではあるが、これらの導入で多彩な環境への対応が見込まれる。

■ フォルダ構成

  TestApp.exe
    実行ファイル。
    起動するとゲーム画面を想定した画面が表示される。

  bgm
    .wav .ogg .mp3 を格納するフォルダ。

  font
    .ttf を格納するフォルダ。

  image
    .png を格納するフォルダ。

  object
    非公開フォルダ。

  se
    .wav .ogg .mp3 を格納するフォルダ。

  sprite
    アニメーションパターンを定義したjsonを格納するフォルダ。

■ アプリ使用方法

  TestApp.exe を起動すると自機のようなものが表示される。
  カーソルキーやジョイスティックで動かすことが可能。

  ウィンドウは自由にサイズを変更可能。
  中央のゲーム画面はいかなるウィンドウサイズになってもアス比を維持しようとする。

  Fキー : フルスクリーンとウィンドウモードの切替
  Tキー : テスト画面を表示(アーケード基板でテストボタンを押したときに表示される内容を想定)

  テスト画面ではテクスチャデータ、スプライトデータ、フォントデータ、BGM、SEを表示したり鳴らしたりできる。
  上記のフォルダにファイルを置くことで自動的に認識される。
  試しに何かファイルを置いて当アプリで表示していただきたい。

■ 著作権について

  当テストアプリで使用されているリソース(bgm、font、image、se)は著作権表示不要のフリー素材を使用している。
  それ以外のファイルについては再配布は禁止である。

以上
