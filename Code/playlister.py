class playlister:
	def __init__(genre_list, song_list):
		print "playlister\n"
		print "1. Make a playlist"
		print "2. Load a playlist"
		print "press E to exit"
		while:
			choice = getch()
			if choice == 1:
				self.choose_genre(genre_list)
			elif choice == 2:
				self.load_playlist()
			elif choice == 'e' or choice == 'E':
				break

	def choose_genre(genres):
		print "choose genre:"
		i=0
		for genre in genres:
			i+=1
			print i, genre
		
		while:
			if user_input = getch() <= 0 or user_input > i:
				choice = genres[user_input-1]
				user_input = getch()
				break

	def how_many_songs(genre):
		size = input("how many songs?\n")


	def give_name(size):
		# input name
		# save

	def load_playlist():
		# ask name

	def edit_playlist(playlist):
		# sort by popularity
		# sort by name

	def delete_song():
		# ask number
		# overwrite
		# save new > give_name

# pra user input sem aguardar o enter
class _Getch:
    def __init__(self):
        try:
            self.impl = _GetchWindows()
        except ImportError:
            self.impl = _GetchUnix()

    def __call__(self): 
    	return self.impl()


class _GetchUnix:
    def __init__(self):
        import tty, sys

    def __call__(self):
        import sys, tty, termios
        fd = sys.stdin.fileno()
        old_settings = termios.tcgetattr(fd)
        try:
            tty.setraw(sys.stdin.fileno())
            ch = sys.stdin.read(1)
        finally:
            termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
        return ch


class _GetchWindows:
    def __init__(self):
        import msvcrt

    def __call__(self):
        import msvcrt
        return msvcrt.getch()


getch = _Getch()