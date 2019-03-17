pipeline {
    agent {
        dockerfile {
            filename 'Dockerfile'
        }
    }

    stages {

        stage ('pre-analysis') {
            steps {
                sh 'cppcheck --enable=all --std=c+11 --inconclusive --xml --xml-version=2 . 2> cppcheck_report.xml'
                //sh 'cppcheck --enable=warning,performance,portability,information,missingInclude \
                //    --std=c++11 --library=qt.cfg --verbose --quiet \
                //    --template="[{severity}][{id}] {message} {callstack} (On {file}:{line})" \
                //    `git ls-files "*.hpp" "*.cpp"` '
            }
        }

        stage ('build'){
            steps {
                dir('build')
                {
                    sh 'cmake ..'
                    sh 'make'
                }
            }
        }
    }
    post {
	always {
	    publishCppcheck pattern:'cppcheck_report.xml'
	}        
    }
}
