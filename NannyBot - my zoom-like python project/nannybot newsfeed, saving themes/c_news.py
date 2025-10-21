from random import random

import PySide6.QtCore
import newspaper
import numpy.random

from newspaper import article
from newspaper import *

'''must be qobject to emit signal. i made it qthread (that inherits from qobject) because it takes it forever to load'''


class w_newsfeed(PySide6.QtCore.QThread):
    sig_sendNews = PySide6.QtCore.Signal(str)

    def __init__(self):
        super().__init__()

    def run(self) -> None:
        self.newsfeed()

    def newsfeed(self) -> None:
        nature = newspaper.build('https://www.sciencenews.org/topic/physics', memoize_articles=False)
        '''for article in nature.articles:
            print(article.url)
        '''
        import random

        i = numpy.random.random_integers(0, 30)
        firstArticle = nature.articles[i]
        firstArticle.download()
        firstArticle.parse()

        urlLink = "<a href=\"" + firstArticle.url + "\">" + firstArticle.title + "</a>"
        self.sig_sendNews.emit(urlLink)